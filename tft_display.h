#ifndef _tft_display_h
#define _tft_display_h
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include "interface.h"
#include <Fonts/GFXFF/FreeSansBoldOblique72pt7b.h>
/************************************************************************************************************************/
class lcd_tft
{
  public:
    void displayDownloadedImageData(byte x, byte y, byte w, byte h);
    void oled_init(void);//ham cai dat oled
    void fresh(void);
    void logo_wifi(int rssi);//hien thi cuong do wifi
    void SETUP_model(String model);//hien thi thong tin IOT
    void processId(String processid);//hien thi process id
    void timer(void);//hien thi hour, minte, second
    void SETUP_project(void);//hien thi thong tin project
    void loading(uint8_t data, String ssid, String mac, String rssi);//loading thong tin wifi
    void status_machine(void);//hien thi trang thai may
    void display_data(void); //hien thi thong tin
    void main_display(void);//hien thi man hinh chinh
    void update_data(void);
    void menu(void);
    void display_connect(String ssid, String pass);//hien thi ket noi wifi
    void wifi_result(bool status_wifi);//hien thi ket qua ket noi wifi
    //private:

};


#endif
