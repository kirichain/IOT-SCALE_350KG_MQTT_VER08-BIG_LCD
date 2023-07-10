//Version full with Text Display
#include <Arduino.h>
#include <stdio.h>
#include "wifi.h"
#include <functional>
#include "tft_display.h"
#include "interface.h"
#include "i2c.h"
#include <Adafruit_PCF8575.h>
#include "event.h"
#include "Mqtt.h"
#include "web.h"
#include "eeprom.h"
#include "json_img_render.h"

var_all             var;
lcd_tft             lcd;    //khai bao function
wifi_function       wifi;   //khai bao function
i2c_function        i2c;
function_event      event;  //khai bao function
Mqtt_Client         Mqtt;
web_function        web;
EEPROM_FUNCTION     EEP;

void function_loop(void);
void IRAM_ATTR ISR_PCF(void);
Adafruit_PCF8575 Expander;

void setup()
{
  // put your setup code here, to run once:
  /************************************************************************************************************************/
  //Setup Io

  if (!Expander.begin(0x20, &Wire)) ESP.reset();
  Serial.begin(9600);.l
  Expander.pinMode(KEY_ENTER, INPUT);
  Expander.pinMode(KEY_UP, INPUT);
  Expander.pinMode(IN_SAMPLE, INPUT);
  Expander.pinMode(PCF3, INPUT);
  Expander.pinMode(PCF4, INPUT);
  Expander.pinMode(PCF5, INPUT);
  Expander.pinMode(PCF6, INPUT);
  Expander.pinMode(PCF7, INPUT);
  Expander.pinMode(OK_LAMP1, OUTPUT);
  Expander.pinMode(OK_LAMP, OUTPUT);
  Expander.pinMode(NG_LAMP, OUTPUT);
  Expander.pinMode(SVR_LAMP, OUTPUT);
  Expander.pinMode(BUZZER, OUTPUT);
  Expander.pinMode(PCF13, OUTPUT);
  Expander.pinMode(PCF14_S1, OUTPUT);
  Expander.pinMode(PCF15_S0, OUTPUT);

  pinMode (10, INPUT_PULLUP);
  pinMode (9, INPUT_PULLUP);
  pinMode (PCF_INT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PCF_INT), ISR_PCF, FALLING);
  //  /************************************************************************************************************************/
  //  //Setup Status Io first
  Expander.digitalWrite(BUZZER, LOW);   //BUZZER OFF
  Expander.digitalWrite(OK_LAMP1, LOW); //OK_LAMP1 OFF
  Expander.digitalWrite(OK_LAMP, LOW);  //OK_LAMP OFF
  Expander.digitalWrite(NG_LAMP, LOW);  //NG_LAMP OFF
  Expander.digitalWrite(SVR_LAMP, LOW); //Server disconnect
  Expander.digitalWrite(PCF14_S1, LOW);
  Expander.digitalWrite(PCF15_S0, LOW);

  EEPROM.begin(512);
  EEPROM.get(EEP_ADR_LCD_ROTATE, var.lcd.rotate);
  EEPROM.get(EEP_ADR_LCD_CONTRATS, var.lcd.contrats);
  //Setup OLED
  lcd.oled_init();
  __asm__ __volatile__ ("nop\n\t");
  lcd.SETUP_project();
  __asm__ __volatile__ ("nop\n\t");

  var.rtu.Status = 0;
  var.machine.Ip = "-";
  var.machine.Id = "-";
  var.machine.Iot_code = "SSFT";
  var.machine.Iot_model = "DAQ-S01";
  var.machine.sProcess = PROCESS_EMPTY;
  var.machine.Old_sProcess = PROCESS_EMPTY;
  var.machine.sProcess_menu = PROCESS_EMPTY;

  /////***************SCALE
  EEPROM.get(EEP_ADR_SCALE_SAMPLE, var.scale.Sample);
  (var.scale.Sample <= 0) ? (var.scale.Sample = 99) : (var.scale.Sample);
  EEPROM.get(EEP_ADR_SCALE_TOLERANCE_P, var.scale.Tolerance_p ); //doc gia tri var.sensor.filter
  (var.scale.Tolerance_p >= 250) ? (var.scale.Tolerance_p = 0) : (var.scale.Tolerance_p );
  EEPROM.get(EEP_ADR_SCALE_TOLERANCE_N, var.scale.Tolerance_n);
  (var.scale.Tolerance_n >= 250) ? (var.scale.Tolerance_n = 0) : (var.scale.Tolerance_n);
  EEPROM.get(EEP_ADR_SCALE_OK_BOX, var.scale.Ok_Box);
  EEPROM.get(EEP_ADR_SCALE_NG_BOX, var.scale.Ng_Box);
  var.scale.Sum_box = var.scale.Ok_Box + var.scale.Ng_Box;

  EEPROM.get(EEP_ADR_PG_QTY, var.scale.Pg_Qty);
  EEPROM.get(EEP_ADR_PO_QTY, var.scale.Po_Qty);
  EEPROM.get(EEP_ADR_UNIT_BOX, var.scale.Units);

  EEPROM.get(EEP_ADR_PO_CODE, var.scale.eep_po);
  var.scale.Pocode = String(var.scale.eep_po);
  EEPROM.get(EEP_ADR_STYLE_CODE, var.scale.eep_style);
  var.scale.Style_Code = String(var.scale.eep_style);
  EEPROM.get(EEP_ADR_GROUP_CODE, var.scale.eep_group);
  var.scale.PackageGroup = String(var.scale.eep_group);

  //////**************END SCALE

  ////***************WIFI & SERVER
  EEPROM.get(EEP_ADR_WIFI_SSID, var.wifi.eepSsid);
  var.wifi.ssid = String(var.wifi.eepSsid);
  EEPROM.get(EEP_ADR_WIFI_PASS, var.wifi.eepPass);
  var.wifi.pass = String(var.wifi.eepPass);
  EEPROM.get(EEP_ADR_MQTT_HTTP_PORT, var.mqtt.httpPort);
  EEPROM.get(EEP_ADR_MQTT_ADDRESS, var.mqtt.Array);
  var.mqtt.Address = String(var.mqtt.Array);
  ////*************LCD*************************
  //EEPROM.get(EEP_ADR_LCD_FONTMODE, var.lcd.rotate);
  //  if (var.lcd.rotate == 0) var.lcd.fontmode = 0;
  //  else var.lcd.fontmode = 1;

  //******************MODBUS******************
  EEPROM.get(EEP_ADR_MODBUS_IDSLAVE, var.rtu.IDslave);
  EEPROM.get(EEP_ADR_MODBUS_BAURATE, var.rtu.Baurate);
  EEPROM.get(EEP_ADR_MODBUS_FORMAT, var.rtu.Format);
  EEPROM.commit();
  var.lcd.hardware = "DAQ0";
  var.lcd.software = "SC00";//Tong <= 10 char
  var.lcd.y_postion = 0;
  var.lcd.page = LCD_PAGE_RUN;
  var.wifi.Strenght = 0;
  var.wifi.STATUS = 0;
  //  var.wifi.ssid = "PKMchine";
  //  var.wifi.pass = "IOT2018";
  //  var.wifi.ssid = "SFS OFFICE";
  //  var.wifi.pass = "sfs#office!@";
  //  var.mqtt.Address = "125.234.135.55";
  var.mqtt.Port = 1883;
  var.mqtt.Connected = 0;
  var.web.Config = 0;
  //EEPROM.end();
  /************************************************************************************************************************/

  /************************************************************************************************************************/
  wifi.wifi_init();
  __asm__ __volatile__ ("nop\n\t");
  /************************************************************************************************************************/
  var.wifi.Mac = wifi.mac(0);
  lcd.display_connect(var.wifi.ssid, var.wifi.pass);
  wifi.wifi_connect(var.wifi.ssid, var.wifi.pass);
  var.wifi.STATUS = WiFi.isConnected();
  lcd.wifi_result(var.wifi.STATUS);
  var.wifi.Mac_Ap = wifi.mac_ap();
  var.machine.Ip = wifi.wifi_ip();
  /********************************Setup Mqtt******************************************/
  Mqtt.Setup_Mqtt();
  /********************************Setup Http******************************************/
  web.Setup_Http();
  event.ISR_Time_Setup();//Not use delay function
  i2c.Install();
  i2c.Request_cmd();
  var.scale.Weight_old = var.scale.Weight;
  lcd.main_display();
  Serial.begin(9600); //OFF de su dung INPUT SAMPLE
  Serial.setTimeout(500);
  //attachInterrupt(digitalPinToInterrupt(PCF_INT), ISR_PCF, FALLING);
  /********************************Watchdog******************************************/
  ESP.wdtDisable();
  ESP.wdtEnable(8);
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
void loop()
{

  //put your main code here, to run repeatedly:
  ESP.wdtFeed();
  function_loop();
  yield();

}
/*****************************************************************************************************************/
void function_loop(void)
{
  if (var.lcd.page == LCD_PAGE_RUN)
  {
    switch (var.machine.sProcess)
    {
      /***************EVENT PUBLISH DATA MACHINE TIME TO SERVER***********/
      case PROCESS_MQTT_PUB_MACHINE_TIME:
        if ((var.mqtt.Connected == 1) && (var.wifi.STATUS == 1))
        {
          Mqtt.Pub_Machine_Time();
          var.sTime.Machine_Time = 0;
        }
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      /***************EVENT PUBLISH DATA TEACHING TO SERVER****************/
      case PROCESS_MQTT_PUB_TEACHING:
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      /**************EVENT PUBLISH DATA STATUS IOT TO SERVER**************/
      case PROCESS_MQTT_PUB_STATUS:
        if ((var.mqtt.Connected == 1) && (var.wifi.STATUS == 1))
        {
          Mqtt.Pub_Iot_Status();
          var.sTime.Mqtt_Status = 0;
        }
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      /****************PROCESS MQTT RECONNECT**************************/
      case PROCESS_MQTT_RECONNECT:
        if (var.wifi.STATUS == 1)
        {
          Mqtt.Reconnect();
        }
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      /*****************EVENT CONTROLL LED******************************/
      case PROCESS_CONTROLL_LED:
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      /*******************EVENT EMPTY***********************************/
      case PROCESS_OTA_UPDATE:
        web.Ota();
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_SCALE_ZERO:
        var.machine.sProcess = PROCESS_EMPTY;
        __asm__ __volatile__ ("nop\n\t");
        __asm__ __volatile__ ("nop\n\t");
        __asm__ __volatile__ ("nop\n\t");
        break;
      case PROCESS_SCALE_SAMPLE:
        var.scale.Sample = var.scale.Weight;
        var.scale.Ok_Box = 0;
        var.scale.Ng_Box = 0;
        var.scale.Sum_box = 0;
        EEP.write_setup_teaching();
        __asm__ __volatile__ ("nop\n\t");
        __asm__ __volatile__ ("nop\n\t");
        __asm__ __volatile__ ("nop\n\t");
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_SCALE_DATA:
        EEP.write_scale_data();
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_WIFI_RECONNECT:
        WiFi.reconnect();
        var.wifi.Reconnect_count = 0;
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_PO_CODE:
        EEP.write_po_code();
        var.lcd.update_data = 4;
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_PO_STYLE_CODE:
        EEP.write_po_code();
        EEP.write_style_code();
        EEP.write_group_code();
        EEP.write_pg_qty();
        EEP.write_po_qty();
        EEP.write_units_box();
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_OK_LAMP:
        Expander.digitalWrite(OK_LAMP1, HIGH);
        Expander.digitalWrite(OK_LAMP, HIGH);
        Expander.digitalWrite(NG_LAMP, LOW);
        Expander.digitalWrite(BUZZER, LOW);
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_NG_LAMP:
        Expander.digitalWrite(OK_LAMP1, LOW);
        Expander.digitalWrite(OK_LAMP, LOW);
        Expander.digitalWrite(NG_LAMP, HIGH);
        Expander.digitalWrite(BUZZER, HIGH);
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_NONE_LAMP:
        Expander.digitalWrite(OK_LAMP1, LOW);
        Expander.digitalWrite(OK_LAMP, LOW);
        Expander.digitalWrite(NG_LAMP, LOW);
        Expander.digitalWrite(BUZZER, LOW);
        var.machine.sProcess = PROCESS_EMPTY;
        break;
      case PROCESS_EMPTY:
      default:
        //******************CACULATE SCALE****************
        event.Check_scale();
        if ((var.scale.Check_begin == 0) && (var.scale.Check_end == 1))
        {
          if (var.sload.pStatus == 1) var.scale.Ok_Box += 1;
          else var.scale.Ng_Box += 1;
          var.scale.Sum_box = var.scale.Ok_Box + var.scale.Ng_Box;
          var.scale.Pub = 1;
          var.scale.Check_end = 0;
          var.lcd.update_data = 2;
        }
        //******************END SCALE*********************
        //******************BARCODE READ******************
        if (Serial.available() != 0)
        {
          String comp1 = "@po@";
          String comp2 = "";
          String code = "";
          int check;
          code = Serial.readStringUntil('\n');
          code.trim();
          comp2 = (String)code.substring(0, 4);
          check = comp2.equalsIgnoreCase(comp1);
          //Process String Boxcode or PoCode
          if (check != 0)
          {
            var.scale.Pocode = (String)code.substring(4);
            var.machine.sProcess = PROCESS_EEP_PO_CODE;
          }
          else
          {
            Mqtt.Get_Sub_UART(code);
          }
        }
        //******************END BARCODE*******************
        //********************TIMES***********************
        var.sTime.t_second  = second();
        if (var.sTime.t_old  != var.sTime.t_second)
        {
          var.sTime.t_old = var.sTime.t_second;
        }
        if (var.sTime.t_second == 0)
        {
          var.sTime.t_min  = minute();
          __asm__ __volatile__ ("nop\n\t");
          var.sTime.t_year = year();
          __asm__ __volatile__ ("nop\n\t");
          var.sTime.t_mon = month();
          __asm__ __volatile__ ("nop\n\t");
          var.sTime.t_day = day();
          __asm__ __volatile__ ("nop\n\t");
          var.sTime.t_hour = hour();
        }
        if (var.sTime.t_year <= 2018) var.sTime.update_finish = 0;
        break;
    }
    /***********************FUNCTION DISPLAY OLED***********************/
    if (var.lcd.Fresh == 0)
    {
      lcd.update_data();
      var.lcd.update_data = 10;
    }
    else
    {
      lcd.main_display();
      var.lcd.Fresh = 0;
    }
  }
  else
    /*******************FUNCTION MENU SETTING*********************************/
  {
    lcd.menu();
    web.handle_Client();
    switch (var.machine.sProcess_menu)
    {
      case PROCESS_WEB_SERVER_CONFIG:
        var.web.Config = 1;//flag web
        __asm__ __volatile__ ("nop\n\t");
        web.Setup_Web();
        __asm__ __volatile__ ("nop\n\t");
        __asm__ __volatile__ ("nop\n\t");
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_MENU_TEACHING:
        EEP.write_setup_teaching();
        lcd.main_display();
        var.lcd.page = LCD_PAGE_RUN;
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_WEB_NETWORK:
        EEP.write_web_network();
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_WEB_SERVER:
        EEP.write_web_server();
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_SETUP_MONITOR:
        EEP.write_setup_monitor();
        if (var.lcd.y_postion == 3)
        {
          var.lcd.page = LCD_PAGE_MENU_SETUP;
        }
        else if (var.lcd.y_postion == 4)
        {
          lcd.main_display();
          var.lcd.page = LCD_PAGE_RUN;
        }
        var.lcd.y_postion = 0;
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_SETUP_MODBUS:
        EEP.write_setup_modbus();
        if (var.lcd.y_postion == 3)
        {
          var.lcd.page = LCD_PAGE_MENU_SETUP;
        }
        else if (var.lcd.y_postion == 4)
        {
          var.lcd.page = LCD_PAGE_RUN;
          lcd.main_display();
        }
        var.lcd.y_postion = 0;
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EEP_SCALE_DATA:
        EEP.write_scale_data();
        var.scale.Pub = 1;
        var.Plan.ProcessId = "C.RS";
        var.machine.sProcess_menu = PROCESS_EMPTY;
        break;
      case PROCESS_EMPTY:
      default:
        break;
    }
  }
}

//=============================================================
void IRAM_ATTR ISR_PCF(void)
{
  if ((millis() - var.scale.old_time) <= 90)
  {
    return;
  }
  var.scale.old_time = millis();

  if (Expander.digitalRead(KEY_ENTER) == 0)
  {
    lcd.fresh();
    ISR_ENTER();
    //if (var.lcd.Fresh == 1)lcd.fresh();
  }
  else if (Expander.digitalRead(KEY_UP) == 0)
  {
    ISR_UP();
  }
  else if (Expander.digitalRead(IN_SAMPLE) == 0)
  {
    if (var.lcd.page != LCD_PAGE_RUN) lcd.fresh();
    ISR_SAMPLE();
  }
  else
  {
    return;
  }
}
//==============================================
