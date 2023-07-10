#ifndef _wifi_h
#define _wifi_h
#include <ESP8266WiFi.h>
class wifi_function
{
  public://co the goi bat ky dau
    int num_networks(void);// doc so luong wifi co the connect
    void wifi_init(void);// cai dat wifi
    String ssid(int chanel);//ham tra ve gia tri ten mang ssid
    String mac(int chanel);//ham tra ve dia chi mac
    String mac_ap(void);
    String wifi_ip(void);//ham tra ve dia chi ip
    int wifi_rssi(int chanel);//ham tra ve cuong do wifi
    String wifi_connected(void);// tra lai ten ham da ket noi
    bool wifi_connect(String ssid, String pass);//thuc hien kiem ket noi wifi
    //private:
};
#endif
/************************************************************************/
