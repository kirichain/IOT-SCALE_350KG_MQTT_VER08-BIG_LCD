#ifndef _event_h
#define _event_h
#include <Ticker.h>
#include "interface.h"
#include "wifi.h"
#include "i2c.h"
#include "Mqtt.h"

void ISR_UP(void);//FUNCTION INTERRUPT DELARCE
void ISR_ENTER(void);//FUNCTION INTERRUPT ENTER
void ISR_ZERO(void);//FUNCTION INTERRUPT SENSOR
void ISR_SAMPLE(void);//FUNCTION INTERRUPT SAMPLE
void ISR_TIME500MS(void);
void ISR_TIME1S(void);//FUNCTION INTERRUPT TIME 1S
void ISR_TIME3S(void);//FUNCTION INTERRUPT TIME 3S

/************************************************************************************************************************/
class function_event
{
  public:
    void ISR_Time_Setup(void);
    void Check_scale(void);
    //private:

};
extern function_event  event;
#endif
/************************************************************************************************************************/
