#ifndef MHZ19B_SERIAL_H
#define MHZ19B_SERIAL_H

#include "SoftwareSerial.h"

#define TIMEOUT_COUNT 5
#define MSG_LENGTH 9
#define SUCCESS 1
#define TIMEOUT_ERROR 2 

class Mhz19bSerial{
private:
    const byte CALIB_ZERO[MSG_LENGTH] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78};
    const byte CALIB_OFF[MSG_LENGTH] = {0xFF,0x01,0x79,0x00,0x00,0x00,0x00,0x00,0x86};
    const byte GET_C02[MSG_LENGTH] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
    SoftwareSerial *_serial;

    byte _getResponse(unsigned char responseBuffer[MSG_LENGTH]);

    unsigned char _getCheckSum(unsigned char packet[MSG_LENGTH]);
public:
    Mhz19bSerial(byte rxPin, byte txPin);
    ~Mhz19bSerial();

    byte setCalibrationOff();
    byte zeroCalibration();
    unsigned int getC02();
};

#endif // ! MHZ19B_SERIAL_H