#ifndef _i2c_h
#define _i2c_h
#include <Wire.h>

#include <String.h>

class i2c_function
{
  public:
    void Install(void);
    void Send_cmd(uint8_t cmd);
    void Request_cmd(void);
};
extern i2c_function  i2c;
#endif
