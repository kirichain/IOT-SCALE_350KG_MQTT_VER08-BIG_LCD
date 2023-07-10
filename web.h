#ifndef _web_h_
#define _web_h_

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

bool downloadAndDisplayImage(char *url, char *filename, byte method);

void NOT_FOUND_API(void);

void handleRoot(void);

void data_web_config(void);

bool Submit_Network(void);

bool Submit_Server(void);

bool Submit_Location(void);

bool Submit_Machine(void);

bool Submit_Modbus(void);

class web_function {
public://co the goi bat ky dau
    void Setup_Http(void);

    void Setup_Web(void);

    void handle_Client(void);

    void Ota(void);

    void Creat_Hmi(void);
    //private:
};

extern web_function web;
#endif
/************************************************************************/
