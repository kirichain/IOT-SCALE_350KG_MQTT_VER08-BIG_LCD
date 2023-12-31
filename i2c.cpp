#include <arduino.h>
#include "interface.h"
#include "i2c.h"


/************************************************************************************************************************/
void i2c_function::Install(void)
{
  Wire.begin();
  //Expander.begin();
}
/************************************************************************************************************************/
void i2c_function::Send_cmd(uint8_t cmd)
{
  byte error;
  Wire.beginTransmission(0x01);
  Wire.write(cmd);
  error = Wire.endTransmission(0x01);
}
/************************************************************************************************************************/
void i2c_function::Request_cmd(void)
{
  byte byte_receive;
  bool data_break = 0;
  long over_time = 0;
  String temp = "";
  byte_receive = Wire.requestFrom(0x01, 6);
  if (byte_receive != 6) return;
  over_time = millis();
  while (Wire.available() != 0) // slave may send less than requested
  {
    char c = Wire.read();    // receive a byte as character
    if ((c != 255) && (c != '=') && (c != '\0') && (c != '\n')) temp += String(c);
    //Process to Overtime if I2c loop
    if (millis() - over_time >= 373)      return;//333
  }
  //Serial.println(temp);
  if (temp.toFloat() == 0) return;
  else var.scale.Weight = round(temp.toFloat() * 100) / 100.0;

}
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
