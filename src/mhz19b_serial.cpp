#include "mhz19b_serial.h"

byte Mhz19bSerial::_getResponse(unsigned char responseBuffer[MSG_LENGTH])
 {
    int i = 0;
    memset(responseBuffer, 0, MSG_LENGTH);

    while (_serial->available() == 0) {
        delay(1000);
        i++;

        if (i > TIMEOUT_COUNT)
            return TIMEOUT_ERROR;
    }
        
    if (_serial->available() > 0) {
        _serial->readBytes(responseBuffer, 9);
    }
}

unsigned char Mhz19bSerial::_getCheckSum(unsigned char packet[MSG_LENGTH]) {
    byte i;
    unsigned char checksum = 0;
    for (i = 1; i < 8; i++) {
        checksum += packet[i]; 
    }
    checksum = 0xff - checksum;
    checksum += 1;
    return checksum;
}

Mhz19bSerial::Mhz19bSerial(byte rxPin, byte txPin){
    _serial = new SoftwareSerial(rxPin, txPin);
    _serial->begin(9600);
}

Mhz19bSerial::~Mhz19bSerial(){
    delete _serial;
}

byte Mhz19bSerial::setCalibrationOff(){
    unsigned char response[MSG_LENGTH]; 
    _serial->write(CALIB_OFF, MSG_LENGTH);
    return _getResponse(response);
}

byte Mhz19bSerial::zeroCalibration(){
    unsigned char response[MSG_LENGTH]; 
    _serial->write(CALIB_ZERO, MSG_LENGTH);
    return _getResponse(response);
}

unsigned int Mhz19bSerial::getC02(){    
    _serial->write(GET_C02, MSG_LENGTH);
        
    unsigned char response[MSG_LENGTH]; 
    byte responceError = _getResponse(response);
    if (responceError > SUCCESS)
      return responceError;

    unsigned char check = _getCheckSum(response);
    if (response[8] != check) {
        return 0;
    }

    unsigned int responseHigh = (unsigned int) response[2];
    unsigned int responseLow = (unsigned int) response[3]; 

    return (256 * responseHigh) + responseLow; 
}