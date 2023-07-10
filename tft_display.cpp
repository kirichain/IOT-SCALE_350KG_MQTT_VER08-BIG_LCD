#include <TFT_eSPI.h>

#include <arduino.h>
#include "tft_display.h"


//extern const uint8_t Large72RLE[];
TFT_eSPI tft = TFT_eSPI(); // Khai báo đối tượng màn hình TFT

//ham cai dat oled
void lcd_tft::oled_init(void)
{
  tft.begin();
  tft.setRotation(var.lcd.rotate);
  tft.setTextSize(1);
  tft.setFreeFont(&FreeSerifItalic9pt7b);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}
//***********************************************************************************************************************
void lcd_tft::fresh(void)
{
  tft.fillScreen(TFT_BLACK);
}
/************************************************************************************************************************/
//Hien thi rssi cua wifi
void lcd_tft::logo_wifi(int rssi)//only send data
{
  String data;
  int x_draw, Y_draw;
  if (rssi > 100) return;
  data = String(rssi);
  x_draw = (rssi / 20) * 5;
  Y_draw = (rssi * 14) / 100;
  tft.fillTriangle(0, 14, x_draw, 14, x_draw, 14 - Y_draw, TFT_GREEN);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setFreeFont(&FreeSerifItalic9pt7b);
  tft.drawString(data.c_str(), 27, 0);
}
/************************************************************************************************************************/
//hien thi version model hien dang su dung
void lcd_tft::SETUP_model(String model)
{
  // tft.setFont(tft_font_courR08_tr);
  tft.startWrite();
  tft.drawString(model.c_str(), 62, 0 );
  tft.endWrite();
}
///************************************************************************************************************************/
void lcd_tft::processId(String processid)
{
  //tft.setFont(tft_font_courR08_tr);
  tft.startWrite();
  tft.drawString(processid.c_str(), 240, 0);
  tft.endWrite();
}
///************************************************************************************************************************/
void lcd_tft::timer(void)
{
  String h, m, s;
  h = String(var.sTime.t_hour);
  m = String(var.sTime.t_min);
  s = String(var.sTime.t_second);
  //tft.setFont(tft_font_courR08_tr);
  tft.startWrite();
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("NG = ", 200, 0);
  tft.drawString(String(var.scale.Ng_Box).c_str(), 245, 0);
  tft.drawString((h + ": " + m + ": " + s).c_str(), 400, 0);
  tft.endWrite();
}
///************************************************************************************************************************/
////hien thi thong tin project
void lcd_tft::SETUP_project()
{
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeSerifBoldItalic18pt7b);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString( "Wellcome!", 30, 40);
  tft.drawString( "IOT CHECK WEIGHT", 40, 80);
  tft.drawString("IOTPK2*06", 68, 120);
  //tft.fillRing(100, 100, 20, 30, 0, 180, TFT_RED);

}
///************************************************************************************************************************/
////loading phan tram theo data
void lcd_tft::loading(uint8_t data, String ssid, String mac, String rssi)
{
  String data_loading;
  (data >= 100) ? (data = 100) : (data = data);
  data_loading = String(data) + "%loading...";
  tft.startWrite();
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawString(data_loading.c_str(), 0, 160);
  tft.endWrite();
}
///************************************************************************************************************************/
////trang thai cac ngo ra cua may
void lcd_tft::status_machine(void)
{
  String wifi_string, server_string;
  String string_out = "";
  if (var.wifi.STATUS == 1)
    wifi_string = "W-ON";
  else wifi_string = "W-DIS";
  if (var.mqtt.Connected == 1)
    server_string = ",S-ON";
  else server_string = ",S-DIS";

  string_out = wifi_string + server_string;
  if ((var.wifi.STATUS == 1) && (var.mqtt.Connected == 1))
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  else if ((var.wifi.STATUS == 1) || (var.mqtt.Connected == 0))
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  else
    tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.setFreeFont(&FreeMono9pt7b);
  tft.drawString(string_out.c_str(), 55, 0);
}
///************************************************************************************************************************/
void lcd_tft::display_data(void)
{
  String string_weight, sum_box, pcs_box;
  if (var.scale.Weight >= 0.06)
    string_weight = String(var.scale.Weight);
  else if (var.scale.Weight <= (-0.20))
    string_weight = "Negative";
  else string_weight = "0.00";

  pcs_box = String(var.scale.Ok_Box);
  sum_box     = String(var.scale.Sum_box);
  tft.startWrite();
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setFreeFont(&FreeSerifBold9pt7b);

  tft.drawString("Style :", 15, 30);
  tft.drawString(var.scale.Style_Code.c_str(), 90, 30);
  tft.drawString("Barcode :", 15, 50);
  tft.drawString(String(var.scale.Barcode).c_str(), 90, 50);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString("STD WT:", 240, 50);
  tft.drawString(String(var.scale.Sample).c_str(), 320, 50);
  tft.drawString("Pass:", 375, 50);
  tft.drawString(String(var.scale.Ok_Box).c_str(), 420, 50);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setFreeFont(&FreeSansBoldOblique72pt7b);
  tft.drawString(string_weight.c_str(), 180, 85);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setFreeFont(&FreeSerifItalic9pt7b);
  tft.drawString("MES PG:", 190, 225);
  tft.drawString(String(var.scale.PackageGroup).c_str(), 270, 225);
  tft.drawString("PG QTY:", 190, 245);
  tft.drawString(String(var.scale.Pg_Qty).c_str(), 270, 245);
  tft.drawString("PO    :", 190, 266);
  tft.drawString(String(var.scale.Pocode).c_str(), 270, 265);
  tft.drawString("PO QTY:", 190, 285);
  tft.drawString(String(var.scale.Po_Qty).c_str(), 270, 285);
  tft.endWrite();

}
///************************************************************************************************************************/
////hien thi cac thong so khi chay
void lcd_tft::main_display(void)
{
  tft.fillScreen(TFT_BLACK);
  lcd_tft::logo_wifi (var.wifi.Strenght);
  lcd_tft::timer();
  lcd_tft::status_machine();
  tft.drawLine (20, 20, 460, 20, TFT_RED);
  tft.drawLine (20, 23, 460, 23, TFT_RED);
  lcd_tft::display_data ();
}
///************************************************************************************************************************/
void lcd_tft::update_data(void)
{
  String h, m, s;
  String string_weight, st_old_weight;
  if (var.scale.Weight >= 0.06)
  {
    string_weight = String(var.scale.Weight);
  }
  else if (var.scale.Weight <= (-0.20))
    string_weight = "Negative";
  else string_weight = "0.00";
  int len = string_weight.length();
  switch (var.lcd.update_data)
  {
    case 0://wifi
      tft.startWrite();
      tft.fillRect(0, 0, 50, 15, TFT_BLACK);
      lcd_tft::logo_wifi (var.wifi.Strenght);
      tft.endWrite();
      break;
    case 1://Status
      tft.startWrite();
      tft.fillRect(52, 0, 130, 14, TFT_BLACK);
      lcd_tft::status_machine();
      tft.endWrite();
      break;
    case 2://NG
      tft.startWrite();
      tft.fillRect(243, 0, 60, 14, TFT_BLACK);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setFreeFont(&FreeSerifItalic9pt7b);
      tft.drawString(String(var.scale.Ng_Box).c_str(), 245, 0);
      tft.endWrite();
      break;
    case 3://timer
      h = String(var.sTime.t_hour);
      m = String(var.sTime.t_min);
      s = String(var.sTime.t_second);
      tft.startWrite();
      tft.fillRect(400, 0, 80, 14, TFT_BLACK);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.setFreeFont(&FreeSerifItalic9pt7b);
      tft.drawString((h + ": " + m + ": " + s).c_str(), 400, 0);

      tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      tft.fillRect(320, 50, 55, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Sample).c_str(), 320, 50);
      //pass
      tft.fillRect(420, 50, 60, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Ok_Box).c_str(), 420, 50);
      tft.endWrite();
      break;
    case 4://Po Code, Group
    case 5://Style, Po_Qty, Pg_Qty
      tft.startWrite();
      //Style
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setFreeFont(&FreeSerifItalic9pt7b);
      tft.fillRect(90, 30, 390, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Style_Code).c_str(), 90, 30);
      //PackageGroup
      tft.fillRect(270, 255, 210, 17, TFT_BLACK);
      tft.drawString(String(var.scale.PackageGroup).c_str(), 270, 225);
      //PG QTY
      tft.fillRect(270, 245, 210, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Pg_Qty).c_str(), 270, 245);
      //PO
      tft.fillRect(270, 265, 210, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Pocode).c_str(), 270, 265);
      //PO QTY
      tft.fillRect(270, 285, 210, 17, TFT_BLACK);
      tft.drawString(String(var.scale.Po_Qty).c_str(), 270, 285);
      tft.endWrite();
      break;
    case 6://Barcode
      tft.startWrite();
      tft.fillRect(90, 50, 150, 17, TFT_BLACK);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setFreeFont(&FreeSerifBold9pt7b);
      tft.drawString(String(var.scale.Barcode).c_str(), 90, 50);
      tft.endWrite();
      break;
    case 7://Weight
      tft.startWrite();

      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setFreeFont(&FreeSansBoldOblique72pt7b);
      if (len == 4)
      {
        if (var.scale.st_weight_old[3] != string_weight[3])
        {
          tft.fillRect(390, 85, 90, 115, TFT_BLACK);
          tft.drawString(String(string_weight[3]).c_str(), 390, 85);
        }

        if (var.scale.st_weight_old[2] != string_weight[2])
        {
          tft.fillRect(300, 85, 95, 115, TFT_BLACK);
          tft.drawString(String(string_weight[2]).c_str(), 300, 85);
        }

        tft.fillRect(265, 85, 35, 115, TFT_BLACK);
        tft.drawString(String(string_weight[1]).c_str(), 265, 85);

        if (var.scale.st_weight_old[0] != string_weight[0])
        {
          tft.fillRect(170, 85, 95, 115, TFT_BLACK);
          tft.drawString(String(string_weight[0]).c_str(), 170, 85);
        }

        tft.fillRect(80, 85, 90, 115, TFT_BLACK);
      }
      else if (len == 5)
      {
        if (var.scale.st_weight_old[4] != string_weight[4])
        {
          tft.fillRect(390, 85, 90, 115, TFT_BLACK);
          tft.drawString(String(string_weight[4]).c_str(), 390, 85);
        }

        if (var.scale.st_weight_old[3] != string_weight[3])
        {
          tft.fillRect(300, 85, 95, 115, TFT_BLACK);
          tft.drawString(String(string_weight[3]).c_str(), 300, 85);
        }

        tft.fillRect(265, 85, 35, 115, TFT_BLACK);
        tft.drawString(String(string_weight[2]).c_str(), 265, 85);

        if (var.scale.st_weight_old[1] != string_weight[1])
        {
          tft.fillRect(175, 85, 95, 115, TFT_BLACK);
          tft.drawString(String(string_weight[1]).c_str(), 175, 85);
        }

        if (var.scale.st_weight_old[0] != string_weight[0])
        {
          tft.fillRect(80, 85, 95, 115, TFT_BLACK);
          tft.drawString(String(string_weight[0]).c_str(), 80, 85);
        }
      }
      else
      {
        if (string_weight.equals("Negative"))
        {
          tft.fillRect(80, 85, 400, 115, TFT_BLACK);
          tft.setTextColor(TFT_RED, TFT_BLACK);
          tft.setFreeFont(&FreeSansBoldOblique24pt7b);
          tft.drawString(String(string_weight).c_str(), 80, 85);
        }
        else
        {
          tft.fillRect(80, 85, 400, 115, TFT_BLACK);
          tft.setTextColor(TFT_RED, TFT_BLACK);
          tft.setFreeFont(&FreeSansBoldOblique72pt7b);
          tft.drawString("OVER", 80, 85);
        }
      }
      tft.endWrite();
      var.scale.st_weight_old = string_weight;
      break;
    default:
      break;

  }
}
//*************************************************************************************************************************/
void lcd_tft::menu(void)
{
  String convert;

  //lcd_tft::SETUP_model((var.lcd.hardware + "-" + var.lcd.software).c_str());
  if ((var.lcd.old_y_postion == var.lcd.y_postion) && (var.lcd.old_page == var.lcd.page) && (var.lcd.Fresh == 0)) return;
  var.lcd.old_y_postion = var.lcd.y_postion;
  var.lcd.old_page = var.lcd.page;
  var.lcd.Fresh = 0;
  switch (var.lcd.y_postion)
  {
    case 0:
      tft.fillRect(30, 159, 18, 25, TFT_BLACK);//xóa Postion=4
      tft.fillTriangle(30, 40, 30, 60, 43, 50, TFT_RED);
      break;
    case 1:
      tft.fillRect(30, 39 , 18, 25, TFT_BLACK); //xóa Postion=0
      tft.fillTriangle(30, 70, 30, 90, 43, 80, TFT_RED);
      break;
    case 2:
      tft.fillRect(30, 69, 18, 25, TFT_BLACK);//xóa Postion=1
      tft.fillTriangle(30, 100, 30, 120, 43, 110, TFT_RED);
      break;
    case 3:
      tft.fillRect(30, 99, 18, 25, TFT_BLACK);//xóa Postion=2
      tft.fillRect(30, 159, 18, 25, TFT_BLACK);//xóa Postion=4//Case WEB Config
      tft.fillTriangle(30, 130, 30, 150, 43, 140, TFT_RED);
      break;
    case 4:
      tft.fillRect(30, 129, 18, 25, TFT_BLACK);//xóa Postion=3
      tft.fillTriangle(30, 160, 30, 180, 43, 170, TFT_RED);
      break;
    default:
      break;
  }
  switch (var.lcd.page)
  {
    case LCD_PAGE_MENU:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "MENU.", 70, 0);

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "TEACHING", 50, 40);
      tft.drawString( "WEB CONFIG", 50, 70);
      tft.drawString( "SETUP", 50, 100);
      tft.drawString( "INFO", 50, 130);
      tft.drawString( "EXIT", 50, 160);
      break;
    case LCD_PAGE_MENU_TEACHING:
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.drawString("TEACHING.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Sample:", 50, 40);
      convert = String(var.scale.Weight) + "Kg";
      tft.drawString( convert.c_str(), 200, 40);
      tft.drawString( "Tolerance: +", 50, 70);
      convert = String(var.scale.Tolerance_p) + " %.";
      tft.drawString( convert.c_str(), 200, 70);
      tft.drawString("Tolerance: -", 50, 100 );
      convert = String(var.scale.Tolerance_n) + " %.";
      tft.drawString( convert.c_str(), 200, 100);
      tft.drawString("Back", 50, 130 );
      tft.drawString( "Exit", 50, 160);

      break;
    case LCD_PAGE_MENU_WEB_CONFIG:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "CONFIG.", 70, 0);

      tft.fillRect(50, 40, 430, 20, TFT_BLACK);
      tft.fillRect(50, 70, 430, 20, TFT_BLACK);

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Web Config", 50, 100 );
      tft.drawString("Reconect.", 50, 130 );
      tft.drawString( "Exit.", 50, 160);

      break;

    case LCD_PAGE_MENU_SETUP:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "SETUP.", 70, 0);

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString("Counter", 50, 40 );
      tft.drawString( "Monitor LCD", 50, 70);
      tft.drawString( "Modbus RTU", 50, 100);
      tft.drawString("Back", 50, 130 );
      tft.drawString("Exit", 50, 160 );

      break;
    case LCD_PAGE_MENU_SETUP_COUNTER:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "COUNTER.", 70, 0);

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Config", 50, 40);
      tft.drawString( "Setup", 50, 70);
      tft.drawString( "Reset Data", 50, 100);
      tft.drawString("Back", 50, 130 );
      tft.drawString("Exit", 50, 160 );

      break;
    case LCD_PAGE_MENU_SETUP_MONITOR:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "MONITOR.", 70, 0);
      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "LCD ROTATE:", 50, 40);
      convert = "R" + String(var.lcd.rotate * 90);
      tft.drawString( convert.c_str(), 200, 40);
      tft.drawString( "CONTRATS:", 50, 70);
      convert = String(var.lcd.contrats);
      tft.drawString(convert.c_str(), 200, 70 );
      tft.drawString( "FONTMODE:", 50, 100);
      convert = "";
      convert = String(var.lcd.fontmode);
      tft.drawString( convert.c_str(), 200, 100);
      tft.drawString("Back", 50, 130 );
      tft.drawString( "Exit", 50, 160);

      break;
    case LCD_PAGE_MENU_SETUP_MODBUS:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString("MODBUS .", 70, 0 );
      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString("ID Slave:", 50, 40 );
      convert = String(var.rtu.IDslave);
      tft.drawString(convert.c_str(), 200, 40 );
      tft.drawString("BauRate:", 50, 70 );
      switch (var.rtu.Baurate)
      {
        case 0:  convert = "1200"; break;
        case 1:  convert = "2400"; break;
        case 2:  convert = "4800"; break;
        case 3:  convert = "9600"; break;
        case 4:  convert = "19200"; break;
        case 5:  convert = "38400"; break;
        case 6:  convert = "57600"; break;
        default:
          break;
      }

      tft.drawString(convert.c_str(), 200, 70 );
      tft.drawString("Format:", 50, 100 );
      switch (var.rtu.Format)
      {
        case 0: convert = "NONE"; break;
        case 1: convert = "8,1,E"; break;
        case 2: convert = "7,1,E"; break;
        case 3: convert = "8,1,N"; break;
        case 4: convert = "7,1,N"; break;
        case 5: convert = "8,1,O"; break;
        case 6: convert = "7,1,O"; break;
        default:
          break;
      }
      tft.drawString( convert.c_str(), 200, 100);
      tft.drawString( "Back", 50, 130);
      tft.drawString( "Exit", 50, 160);

      break;
    case LCD_PAGE_MENU_INFO:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString( "INFO.", 70, 0);

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Machine", 50, 40);
      tft.drawString( "Network", 50, 70);
      tft.drawString("Modbus RTU", 50, 100 );
      tft.drawString( "Back", 50, 130);
      tft.drawString( "Exit", 50, 160);

      break;
    case LCD_PAGE_MENU_INFO_MACHINE:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.drawString("MACHINE-Info.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Plan", 50, 40);
      tft.drawString( "Teaching", 50, 70);
      tft.drawString("NFC info", 50, 100 );
      tft.drawString("Back", 50, 130 );
      tft.drawString("Exit", 50, 160 );

      break;
    case LCD_PAGE_MENU_INFO_MACHINE_PLAN:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.drawString("PLAN-Info.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "FACTORY:", 20, 40);
      tft.drawString( var.Plan.Factory.c_str(), 150, 40);
      tft.drawString( "LINE:", 20, 70);
      tft.drawString( var.Plan.Line.c_str(), 150, 70);
      tft.drawString("POSITION:", 20, 100 );
      tft.drawString( var.Plan.Location.c_str(), 150, 100);
      tft.drawString( "STYLE:", 20, 130);
      tft.drawString( var.Plan.Style.c_str(), 150, 130);
      tft.drawString("PROCESS:", 20, 160 );
      tft.drawString( var.Plan.sProcess.c_str(), 150, 160);
      tft.drawString( "PROCESSID:", 20, 190);
      tft.drawString(var.Plan.ProcessId.c_str(), 150, 190 );
      tft.drawString( "WORKERID:", 20, 220);
      tft.drawString( var.Plan.WorkerId.c_str(), 150, 220);
      tft.drawString( "TARGET:", 20, 250);

      break;

    case LCD_PAGE_MENU_INFO_MACHINE_TEACHING:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.drawString("TEACHING-Info.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "Sample:", 50, 40);
      tft.drawString( (String(var.scale.Sample) + " Kg").c_str(), 150, 40);

      break;
    case LCD_PAGE_MENU_INFO_NETWORK:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.drawString("NETWORK-Info.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);

      tft.drawString( "SSID :", 50, 40);
      tft.drawString((String(var.wifi.ssid)).c_str(), 150, 40 );
      tft.drawString("P/W :", 50, 70 );
      tft.drawString((String(var.wifi.pass)).c_str(), 150, 70 );
      tft.drawString( "RSSI :", 50, 100);
      tft.drawString((String(var.wifi.Strenght) + "%").c_str(), 150, 100 );
      tft.drawString("SVR :", 50, 130);
      tft.drawString((String(var.mqtt.Address)).c_str(), 150, 130 );
      tft.drawString("IP M/C :", 50, 160 );
      tft.drawString(var.machine.Ip.c_str(), 150, 160 );
      tft.drawString( "Mac :", 50, 190);
      tft.drawString( var.wifi.Mac.c_str(), 150, 190);

      break;
    case LCD_PAGE_MENU_INFO_MODBUS:
      tft.setFreeFont(&FreeMonoBoldOblique18pt7b);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.drawString("MODBUS-Info.", 70, 0 );

      tft.setFreeFont(&FreeSansBoldOblique9pt7b);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString( "ID Slave:", 50, 40);
      convert = String(var.rtu.IDslave);
      tft.drawString( convert.c_str(), 200, 40);
      tft.drawString("BauRate:", 50, 70 );
      switch (var.rtu.Baurate)
      {
        case 0:  convert = "1200"; break;
        case 1:  convert = "2400"; break;
        case 2:  convert = "4800"; break;
        case 3:  convert = "9600"; break;
        case 4:  convert = "19200"; break;
        case 5:  convert = "38400"; break;
        case 6:  convert = "76400"; break;
        default:
          break;
      }

      tft.drawString( convert.c_str(), 200, 70);
      tft.drawString("Format:", 50, 100 );
      switch (var.rtu.Format)
      {
        case 0: convert = "NONE"; break;
        case 1: convert = "8,1,E"; break;
        case 2: convert = "7,1,E"; break;
        case 3: convert = "8,1,N"; break;
        case 4: convert = "7,1,N"; break;
        case 5: convert = "8,1,O"; break;
        case 6: convert = "7,1,O"; break;
        default:
          break;
      }
      tft.drawString( convert.c_str(), 200, 100);
      tft.drawString( "Status:", 50, 130);
      if (var.rtu.Status == 0) tft.drawString( "OFF", 200, 130);
      else tft.drawString("ON", 200, 130 );

      break;
    default:
      break;
  }
}

///************************************************************************************************************************/
//
///************************************************************************************************************************/
void lcd_tft::display_connect(String ssid, String pass)
{
  String data_ssid;
  tft.fillScreen(TFT_BLACK);
  tft.drawString(data_ssid.c_str(), 30, 90);
  tft.drawString("WIFI CONNECTING...", 50, 90);
}

///************************************************************************************************************************/
void lcd_tft::wifi_result(bool status_wifi)
{
  tft.fillScreen(TFT_BLACK);
  if (var.wifi.STATUS == 1)
  {
    tft.setFreeFont(&FreeSansBoldOblique9pt7b);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("WIFI CONNECT OK", 50, 90);
  }
  else
  {
    tft.setFreeFont(&FreeSansBoldOblique9pt7b);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("WIFI DISCONNECT.", 50, 90);
    tft.drawString("RESET, Please!", 50, 120);

  }

}

/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
