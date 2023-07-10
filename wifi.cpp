#include <arduino.h>
#include "wifi.h"
/************************************************************************************************************************/
int wifi_function::num_networks(void)
{
  int num;
  num = WiFi.scanNetworks();
  return num;
}
/************************************************************************************************************************/
void wifi_function::wifi_init(void)
{
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  WiFi.enableAP(0);
  WiFi.enableSTA(1);
  WiFi.setAutoConnect(true);    //add new at 05-09-2019
  WiFi.setAutoReconnect(true);
  
}
/************************************************************************************************************************/
String wifi_function::ssid(int chanel)
{
  String data;
  data = WiFi.SSID(chanel);
  return data;
}

/************************************************************************************************************************/
String wifi_function::mac(int chanel)
{
  String data;
  data = WiFi.macAddress();
  return data;
}

/************************************************************************************************************************/
String wifi_function::mac_ap(void)
{
  String data;
  data = WiFi.BSSIDstr();
  return data;
}
/************************************************************************************************************************/
String wifi_function::wifi_ip(void)
{
  String data;
  data = WiFi.localIP().toString();
  return data;
}
/************************************************************************************************************************/
int wifi_function::wifi_rssi(int chanel)
{
  int32_t value;
  value = WiFi.RSSI(chanel);
  return value;
}
/************************************************************************************************************************/
String wifi_function::wifi_connected(void)//da ket noi
{
  String data;
  data = WiFi.SSID();
  return data;
}
/************************************************************************************************************************/
bool wifi_function::wifi_connect( String ssid, String pass)// tien hanh ket noi
{
  WiFi.begin(ssid.c_str(), pass.c_str());
  WiFi.waitForConnectResult();
  return WiFi.status();
}

/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/