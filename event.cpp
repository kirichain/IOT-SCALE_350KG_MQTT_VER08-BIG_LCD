#include <arduino.h>
#include "event.h"

Ticker    Time_137ms;
Ticker    Time_1S;
Ticker    Time_3S;
/************************************************************************************/
/************************************************************************************/
void ISR_ENTER(void)//RISING INTERRUPT
{
  switch (var.lcd.page)
  {
    case LCD_PAGE_RUN:
      var.lcd.page = LCD_PAGE_MENU;
      break;
    case LCD_PAGE_MENU:

      switch (var.lcd.y_postion)
      {
        case 0:
          var.lcd.page = LCD_PAGE_MENU_TEACHING;
          var.lcd.y_postion = 0;
          break;
        case 1:
          var.lcd.page = LCD_PAGE_MENU_WEB_CONFIG;
          WiFi.enableSTA(0);
          __asm__ __volatile__ ("nop\n\t");
          __asm__ __volatile__ ("nop\n\t");
          __asm__ __volatile__ ("nop\n\t");
          __asm__ __volatile__ ("nop\n\t");
          __asm__ __volatile__ ("nop\n\t");
          __asm__ __volatile__ ("nop\n\t");
          var.lcd.y_postion = 3;
          var.machine.sProcess_menu = PROCESS_WEB_SERVER_CONFIG;
          break;
        case 2:
          var.lcd.page = LCD_PAGE_MENU_SETUP;
          var.lcd.y_postion = 0;
          break;
        case 3:
          var.lcd.page = LCD_PAGE_MENU_INFO;
          var.lcd.y_postion = 0;
          break;
        case 4:
          var.lcd.page = LCD_PAGE_RUN;
          var.machine.sProcess_menu = PROCESS_EMPTY;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_TEACHING:
      switch (var.lcd.y_postion)
      {
        case 0:
          var.scale.Sample = var.scale.Weight;
          var.lcd.Fresh = 1;
          break;
        case 1:
          (var.scale.Tolerance_p >= 50) ? (var.scale.Tolerance_p = 0) : (var.scale.Tolerance_p = var.scale.Tolerance_p + 1);
          var.lcd.Fresh = 1;
          break;
        case 2:
          (var.scale.Tolerance_n >= 50) ? (var.scale.Tolerance_n = 0) : (var.scale.Tolerance_n = var.scale.Tolerance_n + 1);
          var.lcd.Fresh = 1;
          break;
        case 3:
          var.lcd.page = LCD_PAGE_MENU;
          var.lcd.y_postion = 0;
          break;
        case 4:
          var.machine.sProcess_menu = PROCESS_EEP_MENU_TEACHING;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
    case LCD_PAGE_MENU_WEB_CONFIG:
      switch (var.lcd.y_postion)
      {
        case 3:
          var.lcd.page = LCD_PAGE_MENU_WEB_CONFIG;
          var.machine.sProcess_menu = PROCESS_WEB_SERVER_CONFIG;
          var.web.Config = 1;
          var.lcd.Fresh = 1;
          break;
        case 4:
          //var.lcd.page = LCD_PAGE_RUN;
          var.web.Config = 0;//dieu kien de wifi reconnect
          var.machine.sProcess_menu = PROCESS_ESP_RESET;
          ESP.reset();
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_SETUP:
      switch (var.lcd.y_postion)
      {
        case 0:
          var.lcd.page = LCD_PAGE_MENU_SETUP_COUNTER;
          var.lcd.y_postion = 0;
          break;
        case 1:
          var.lcd.page = LCD_PAGE_MENU_SETUP_MONITOR;
          var.lcd.y_postion = 0;
          break;
        case 2:
          var.lcd.page = LCD_PAGE_MENU_SETUP_MODBUS;
          var.lcd.y_postion = 0;
          break;
        case 3:
          var.lcd.page = LCD_PAGE_MENU;
          var.lcd.y_postion = 0;
          break;
        case 4:
          var.lcd.page = LCD_PAGE_RUN;
          var.machine.sProcess_menu = PROCESS_EMPTY;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
      break;

    case LCD_PAGE_MENU_SETUP_MONITOR:
      switch (var.lcd.y_postion)
      {
        case 0://rotate
          (var.lcd.rotate < 3) ? (var.lcd.rotate += 1) : (var.lcd.rotate = 0);
          var.lcd.Fresh = 1;
          break;
        case 1://contrats
          (var.lcd.contrats <= 240) ? (var.lcd.contrats += 10) : (var.lcd.contrats = 0);
          var.lcd.Fresh = 1;
          break;
        case 2://fontmode
          var.lcd.fontmode = !var.lcd.fontmode;
          var.lcd.Fresh = 1;
          break;
        case 3:
          var.machine.sProcess_menu = PROCESS_EEP_SETUP_MONITOR;
          break;
        case 4:
          var.machine.sProcess_menu = PROCESS_EEP_SETUP_MONITOR;
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_SETUP_COUNTER:
      switch (var.lcd.y_postion)
      {
        case 0://Config
          //khong lam gi ca do chua viet xong
          var.lcd.page = LCD_PAGE_MENU_SETUP_COUNTER;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;

        case 1://Setup
          //khong lam gi ca do chua viet xong
          var.lcd.page = LCD_PAGE_MENU_SETUP_COUNTER;
          var.lcd.y_postion = 1;
          var.lcd.Fresh = 1;
          break;

        case 2://Reset data
          var.scale.Ok_Box = 0;
          var.scale.Ng_Box = 0;
          var.scale.Sum_box = 0;
          var.lcd.Fresh = 1;
          var.machine.sProcess_menu = PROCESS_EEP_SCALE_DATA;
          break;

        case 3://Back
          var.lcd.page = LCD_PAGE_MENU_SETUP;
          var.lcd.y_postion = 0;
          break;

        case 4://Exit
          var.lcd.page = LCD_PAGE_RUN;
          var.machine.sProcess_menu = PROCESS_EMPTY;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          var.lcd.Fresh = 0;
          break;
      }
      break;
    case LCD_PAGE_MENU_SETUP_MODBUS:
      switch (var.lcd.y_postion)
      {
        case 0://ID slave
          (var.rtu.IDslave > 250) ? (var.rtu.IDslave = 1) : (var.rtu.IDslave += 1);
          var.lcd.Fresh = 1;
          break;
        case 1://Baurate
          (var.rtu.Baurate >= 6) ? (var.rtu.Baurate = 0) : (var.rtu.Baurate += 1);
          var.lcd.Fresh = 1;
          break;
        case 2://Format
          (var.rtu.Format >= 6) ? (var.rtu.Format = 0) : (var.rtu.Format += 1);
          var.lcd.Fresh = 1;
          break;
        case 3://Back
          var.machine.sProcess_menu = PROCESS_EEP_SETUP_MODBUS;
          break;
        case 4://Exit
          var.machine.sProcess_menu = PROCESS_EEP_SETUP_MODBUS;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_INFO:
      switch (var.lcd.y_postion)
      {
        case 0:
          var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE;
          var.lcd.y_postion = 0;
          break;
        case 1:
          var.lcd.page = LCD_PAGE_MENU_INFO_NETWORK;
          var.lcd.y_postion = 5;
          break;
        case 2:
          var.lcd.page = LCD_PAGE_MENU_INFO_MODBUS;
          var.lcd.y_postion = 5;
          break;
        case 3:
          var.lcd.page = LCD_PAGE_MENU;
          var.lcd.y_postion = 0;
          break;
        case 4:
          var.lcd.page = LCD_PAGE_RUN;
          var.machine.sProcess_menu = PROCESS_EMPTY;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_INFO_MACHINE:
      switch (var.lcd.y_postion)
      {
        case 0:
          var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE_PLAN;
          var.lcd.y_postion = 0;
          break;
        case 1:
          var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE_TEACHING;
          var.lcd.y_postion = 0;
          break;
        case 2:
          var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        case 3:
          var.lcd.page = LCD_PAGE_MENU_INFO;
          var.lcd.y_postion = 0;
          break;
        case 4:
          var.lcd.page = LCD_PAGE_RUN;
          var.machine.sProcess_menu = PROCESS_EMPTY;
          var.lcd.y_postion = 0;
          var.lcd.Fresh = 1;
          break;
        default:
          break;
      }
      break;
    case LCD_PAGE_MENU_INFO_MACHINE_PLAN:
      var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE;
      var.lcd.y_postion = 0;
      break;
    case LCD_PAGE_MENU_INFO_NETWORK:
      var.lcd.page = LCD_PAGE_MENU_INFO;
      var.lcd.y_postion = 1;
      break;
    case LCD_PAGE_MENU_INFO_MODBUS:
      var.lcd.page = LCD_PAGE_MENU_INFO;
      var.lcd.y_postion = 2;
      break;
    case LCD_PAGE_MENU_INFO_MACHINE_TEACHING:
      var.lcd.page = LCD_PAGE_MENU_INFO_MACHINE;
      var.lcd.y_postion = 1;
      break;
    default:
      break;
  }
}
/************************************************************************************************************************/
void ISR_UP(void)
{

  switch (var.lcd.page)
  {
    case LCD_PAGE_MENU_SETUP_COUNTER:
    case LCD_PAGE_MENU_SETUP_MONITOR:
    case LCD_PAGE_MENU_SETUP_MODBUS:
    case LCD_PAGE_MENU_INFO_MACHINE:
    case LCD_PAGE_MENU_SETUP:
    case LCD_PAGE_MENU_TEACHING:
    case LCD_PAGE_MENU_INFO:
    case LCD_PAGE_MENU:

      (var.lcd.y_postion >= 4) ? (var.lcd.y_postion = 0) : (var.lcd.y_postion = var.lcd.y_postion + 1);

      break;
    case LCD_PAGE_MENU_WEB_CONFIG:

      (var.lcd.y_postion >= 4) ? (var.lcd.y_postion = 3) : (var.lcd.y_postion = var.lcd.y_postion + 1);

      break;
    default:
      break;
  }
}
/************************************************************************************************************************/
void ISR_ZERO(void)//RISING INTERRUPT
{


  var.machine.sProcess = PROCESS_SCALE_ZERO;
  var.Plan.ProcessId = "Zero";
}
/************************************************************************************************************************/
void ISR_SAMPLE(void)//RISING INTERRUPT
{

  var.Plan.ProcessId = "SAMP";
  var.lcd.update_data = 2;
  var.machine.sProcess = PROCESS_SCALE_SAMPLE;
}
/************************************************************************************************************************/
void ISR_TIME500MS(void)
{
  var.sTime.Int1 = 1;
  i2c.Request_cmd();
  (var.scale.Counter >= 250) ? (var.scale.Counter = 0) : (var.scale.Counter += 1);
  if (var.scale.Counter % 2 == 0)
  {
    var.scale.delta = var.scale.Weight - var.scale.Weight_old;
    if (var.scale.delta != 0)
    {
      var.lcd.update_data = 7;
      var.scale.Weight_old = var.scale.Weight;
    }
    if ((var.scale.delta <= 0) & (var.scale.Weight >= 1))
    {
      var.scale.Check_begin = 1;
      (var.scale.Pause_counter >= 250) ? (var.scale.Pause_counter = 250) : (var.scale.Pause_counter += 1);
      if (var.scale.Pause_counter >= 3) var.scale.pause_max = 1;
    }
  }

  if (var.scale.Weight < 1)
  {
    var.scale.Check_begin = 0;
    var.scale.Pause_counter = 0;
    var.scale.pause_max = 0;
  }
  var.sTime.Int1 = 0;
}
/************************************************************************************************************************/
void ISR_TIME1S(void)
{
  if (var.sTime.Int1 == 1) return;
  var.sTime.Int2 = 1;
  var.scale.Check = !var.scale.Check;
  Mqtt.Update_Status();//var.mqtt.Connected = MqttClient.connected(); //update server
  (var.sTime.Cycle >= 65000) ? (var.sTime.Cycle = 65000) : (var.sTime.Cycle = var.sTime.Cycle + 1);
  //PROCESS EVENT
  if (var.scale.Pub == 1)
  {
    if ((var.mqtt.Connected == 1) && (var.wifi.STATUS == 1)) //data scale change
    {
      Mqtt.Pub_Scale();
      var.scale.Pub = 0;
      var.scale.Weight_max = 0;
    }
    else
    {
      var.scale.Pub = 0;
      var.scale.Weight_max = 0;
    }
    var.scale.Pause_counter = 0;
    var.scale.pause_max = 0;
    var.machine.sProcess = PROCESS_EEP_SCALE_DATA;
  }
  var.lcd.update_data = 3;
  var.sTime.Int2 = 0;
}
/************************************************************************************************************************/
void ISR_TIME3S(void)
{
  if ((var.sTime.Int1 == 1) || (var.sTime.Int2 == 1)) return;
  //var.wifi.STATUS = WiFi.isConnected();
  //wl_status_t wifiStatus = WiFi.status();
  var.wifi.STATUS = (WiFi.status() == WL_CONNECTED);
  //***********update wifi**************//
  if (var.wifi.STATUS == 1)
  {
    int8_t dB = WiFi.RSSI();
    if (dB <= -110) var.wifi.Strenght = 0;
    else if ((dB > -110) && (dB <= -89)) var.wifi.Strenght = 10;
    else if ((dB > -89) && (dB <= -75)) var.wifi.Strenght = 40;
    else if ((dB > -75) && (dB <= -63)) var.wifi.Strenght = 60;
    else if ((dB > -63) && (dB <= -52)) var.wifi.Strenght = 80;
    else if ((dB > -52) && (dB <= -41)) var.wifi.Strenght = 90;
    else if ((dB > -41) && (dB <= -10)) var.wifi.Strenght = 100;
    if (var.wifi.Old_Strenght != var.wifi.Strenght)
    {
      var.lcd.update_data = 0;
      var.wifi.Old_Strenght = var.wifi.Strenght;
    }
    else   var.lcd.update_data = 1;
  }
  else
  {
    (var.wifi.Reconnect_count >= 200) ? (var.wifi.Reconnect_count = 200) : (var.wifi.Reconnect_count += 1);
    if ((var.web.Config == 0) && (var.wifi.Reconnect_count >= 15))
    {
      var.machine.sProcess = PROCESS_WIFI_RECONNECT;
      __asm__ __volatile__ ("nop\n\t");
      __asm__ __volatile__ ("nop\n\t");
    }
    var.wifi.Strenght = 0;
  }
  (var.sTime.Mqtt_Status >= 6500) ? (var.sTime.Mqtt_Status = 6500) : (var.sTime.Mqtt_Status = var.sTime.Mqtt_Status + 1);
  (var.sTime.Machine_Time >= 6500) ? (var.sTime.Machine_Time = 6500) : (var.sTime.Machine_Time = var.sTime.Machine_Time + 1);
  //**************PROCESS MQTT RECONNECT************************
  if ((var.mqtt.Disconnect == 1) && (var.sTime.Mqtt_Reconnect >= 20))
  {
    var.machine.sProcess = PROCESS_MQTT_RECONNECT;
    var.sTime.Mqtt_Reconnect = 0; //reset wait reconnect

    return;
  }
  //**************Pub IOT INFORMATION****************************
  if ((var.sTime.update_finish == 0) || (var.sTime.Mqtt_Status >= 300) )
  {
    var.machine.sProcess = PROCESS_MQTT_PUB_STATUS;
    return;
  }
  //****************Pub Machine Time***************************
  if (var.sTime.Machine_Time >= var.sTime.info_machine)
  {
    var.machine.sProcess = PROCESS_MQTT_PUB_MACHINE_TIME;
  }

}

/************************************************************************************************************************/
void function_event::ISR_Time_Setup(void)
{
  Time_137ms.attach_ms(137, ISR_TIME500MS);
  Time_1S.attach_ms(1003, ISR_TIME1S);
  Time_3S.attach_ms(3007, ISR_TIME3S);
}
/************************************************************************************************************************/
void function_event::Check_scale(void)
{
  float delta_e = 0, error;
  int percent;
  if (var.scale.Check_begin == 1)
  {
    if (var.scale.pause_max == 0) var.scale.Weight_max = max(var.scale.Weight_max, var.scale.Weight);
    error = var.scale.Weight_max - var.scale.Sample;
    percent = (int)((error * 100) / var.scale.Sample);
    percent = abs(percent);
    if ((percent <= var.scale.Tolerance_p) || (percent <= var.scale.Tolerance_n))
    {
      var.sload.pStatus = 1;
      var.machine.sProcess = PROCESS_OK_LAMP;
      if (var.machine.sProcess == var.machine.Old_sProcess ) return;
      var.machine.Old_sProcess = PROCESS_OK_LAMP;
    }
    else
    {
      var.sload.pStatus = 0;
      var.machine.sProcess = PROCESS_NG_LAMP;
      if (var.machine.sProcess == var.machine.Old_sProcess ) return;
      var.machine.Old_sProcess = PROCESS_NG_LAMP;
    }
    var.scale.Check_end = 1;
  }
  else
  {
    var.machine.sProcess = PROCESS_NONE_LAMP;
    if (var.machine.sProcess == var.machine.Old_sProcess ) return;
    var.machine.Old_sProcess = PROCESS_NONE_LAMP;
  }

}
/************************************************************************************************************************/
/************************************************************************************************************************/
