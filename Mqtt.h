#ifndef _Mqtt_h
#define _Mqtt_h
#include <ArduinoJson.h>
#include <AsyncMqttClient.h>
#include <TimeLib.h>
#include <Ticker.h>
#include "interface.h"

void onMqtt_Connect(bool sessionPresent);
void onMqtt_Disconnect(AsyncMqttClientDisconnectReason reason);
void onMqtt_Msg(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
String MsgIotInfo(String Status);
void Get_Sub_System(String sms);
void Get_Sub_Plan(String sms);
void Get_Sub_Config(String sms);
void Get_Sub_Teaching(String sms);
void Get_Sub_Machine_Id(String sms);
void Get_Sub_Ota(String sms);

class Mqtt_Client
{
  public:
    void Setup_Mqtt(void);
    void Pub_Scale(void);
    void Pub_Machine_Time(void);
    void Pub_Teaching(void);
    void Pub_Iot_Status(void);
    void Update_Status(void);
    void Reconnect(void);
    void Get_Sub_UART(String sms);
    //private:

};
extern Mqtt_Client  Mqtt;
#endif
