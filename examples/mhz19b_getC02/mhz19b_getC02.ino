#include <mhz19b_serial.h>

Mhz19bSerial co2Serial(27, 26); 
  Serial.begin(9600);
  co2Serial.setCalibrationOff();

  int co2ppm = co2Serial.getC02();
  Serial.println(co2ppm);
}
 
void loop()
{

}
