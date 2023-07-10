#include <arduino.h>
#include "Mqtt.h"

AsyncMqttClient MqttClient;

String topic_pub_System = "/SysCtrl";
String topic_pub_Scale = "/Event/Scale";
String topic_pub_Teaching = "/Event/Teaching";
String topic_pub_Machine_time = "/Event/Mchn_time";

String topic_Sub_System = "";
String topic_Sub_Plan = "";
String topic_Sub_Config = "";
String topic_Sub_Teaching = "";
String topic_Sub_Machine_Id = "";
String topic_Sub_Ota = "";

String sms_pub;
String sms_Sub = "";
/************************************************************************************************************************/
void Mqtt_Client::Setup_Mqtt(void)
{
  char server_address[var.mqtt.Address.length()];
  var.mqtt.Address.toCharArray(server_address, var.mqtt.Address.length() + 1);
  MqttClient.setServer(server_address, var.mqtt.Port);
  MqttClient.connect();//dung de ket noi Mqtt
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  var.mqtt.Connected = MqttClient.connected();
  MqttClient.setKeepAlive(73);
  MqttClient.onConnect(onMqtt_Connect);
  MqttClient.onDisconnect(onMqtt_Disconnect);
  MqttClient.onMessage(onMqtt_Msg);


  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");


  sms_pub = MsgIotInfo("OFF");
  MqttClient.setWill( topic_pub_System.c_str(), 2, false, sms_pub.c_str() );
}
/************************************************************************************************************************/
void onMqtt_Connect(bool sessionPresent)
{
  var.mqtt.Connected = MqttClient.connected();
  if (var.mqtt.Connected == 1)//Connnected
  {
    //Subscribe
    topic_Sub_System = "/SysCtrl/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_System.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

    topic_Sub_Plan = "/Plan/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_Plan.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

    topic_Sub_Config = "/Event/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_Config.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

    topic_Sub_Teaching = "/Teaching/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_Teaching.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

    topic_Sub_Machine_Id = "/SysCtrl/MCID/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_Machine_Id.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

    topic_Sub_Ota = "/OTA/" + var.wifi.Mac;
    MqttClient.subscribe(topic_Sub_Ota.c_str(), 0);
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
  }
  else
  {
    MqttClient.connect( );
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
  }

}

/************************************************************************************************************************/
void onMqtt_Disconnect(AsyncMqttClientDisconnectReason reason)
{
  var.mqtt.Connected = MqttClient.connected();
  if (var.mqtt.Connected == 0) var.mqtt.Disconnect = 1;
}
/************************************************************************************************************************/
void onMqtt_Msg(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  uint8_t lenMsg;
  Ticker stop();
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  lenMsg += len;
  sms_Sub += String(payload).substring(0, len);
  if (lenMsg >= total)
  {
    if (String(topic) == topic_Sub_System)              Get_Sub_System(sms_Sub);
    else if (String(topic) == topic_Sub_Plan)           Get_Sub_Plan(sms_Sub);
    else if (String(topic) == topic_Sub_Config)         Get_Sub_Config(sms_Sub);
    else if (String(topic) == topic_Sub_Teaching)       Get_Sub_Teaching(sms_Sub);
    else if (String(topic) == topic_Sub_Machine_Id)     Get_Sub_Machine_Id(sms_Sub);
    else if (String(topic) == topic_Sub_Ota)            Get_Sub_Ota(sms_Sub);
    else
    {
      __asm__ __volatile__ ("nop\n\t");
      __asm__ __volatile__ ("nop\n\t");
    }
    lenMsg = 0;
    sms_Sub = "";
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");

  }
  Ticker update();
  Ticker start();
}
/************************************************************************************************************************/
String MsgIotInfo(String Status)
{
  String msg = "{";
  msg.concat("\"IOT_MAC\":\"");
  msg.concat(var.wifi.Mac);
  msg.concat("\",\"AP_MAC\":\"");
  msg.concat(var.wifi.Mac_Ap);
  msg.concat("\",\"IOT_SPPL_CD\":\"");
  msg.concat(var.machine.Iot_code);
  msg.concat("\",\"IOT_MODEL\":\"");
  msg.concat(var.machine.Iot_model);
  msg.concat("\",\"MCIP\":\"");
  msg.concat(var.machine.Ip);
  msg.concat("\",\"MCID\":\"");
  msg.concat(var.machine.Id);
  msg.concat("\",\"STS\":\"");
  msg.concat(Status);
  msg.concat("\",\"VER\":\"");
  msg.concat(var.lcd.hardware);
  msg.concat("-");
  msg.concat(var.lcd.software);
  msg.concat("\"}");
  return msg;
}

/************************************************************************************************************************/
void Mqtt_Client::Pub_Scale(void)
{
  sms_pub = "";
  sms_pub = "{";
  sms_pub.concat("\"YEAR\":");
  sms_pub.concat(var.sTime.t_year);
  sms_pub.concat(",\"MON\":");
  sms_pub.concat(var.sTime.t_mon);
  sms_pub.concat(",\"DAY\":");
  sms_pub.concat(var.sTime.t_day);
  sms_pub.concat(",\"HOUR\":");
  sms_pub.concat(var.sTime.t_hour);
  sms_pub.concat(",\"MIN\":");
  sms_pub.concat(var.sTime.t_min);
  sms_pub.concat(",\"SEC\":");
  sms_pub.concat(var.sTime.t_second);
  sms_pub.concat(",\"MAC\":\"");
  sms_pub.concat(var.wifi.Mac);
  sms_pub.concat("\",\"PACKAGEGROUP\":\"");
  sms_pub.concat(var.scale.PackageGroup);
  sms_pub.concat("\",\"POCODE\":\"");
  sms_pub.concat(var.scale.Pocode);
  sms_pub.concat("\",\"STYLECODE\":\"");
  sms_pub.concat(var.scale.Style_Code);
  sms_pub.concat("\",\"BARCODE\":\"");
  sms_pub.concat(var.scale.Barcode);
  sms_pub.concat("\",\"BOXPCS\":\"");
  sms_pub.concat(var.scale.Units);
  sms_pub.concat("\",\"CHECK\":\"");
  if (var.sload.pStatus == 1) sms_pub.concat("OK");
  else sms_pub.concat("NG");
  sms_pub.concat("\",\"SAMPLE\":");
  sms_pub.concat(var.scale.Sample);
  sms_pub.concat(",\"WEIGHT\":");
  sms_pub.concat(var.scale.Weight_max);
  sms_pub.concat(",\"OK_BOX\":");
  sms_pub.concat(var.scale.Ok_Box);
  sms_pub.concat(",\"NG_BOX\":");
  sms_pub.concat(var.scale.Ng_Box);
  sms_pub.concat("}");
  MqttClient.publish( topic_pub_Scale.c_str(), 2, false, sms_pub.c_str() );
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Mqtt_Client::Pub_Machine_Time(void)
{
  sms_pub = "";
  sms_pub = "{";
  sms_pub.concat("\"YEAR\":");
  sms_pub.concat(var.sTime.t_year);
  sms_pub.concat(",\"MON\":");
  sms_pub.concat(var.sTime.t_mon);
  sms_pub.concat(",\"DAY\":");
  sms_pub.concat(var.sTime.t_day);
  sms_pub.concat(",\"HOUR\":");
  sms_pub.concat(var.sTime.t_hour);
  sms_pub.concat(",\"MIN\":");
  sms_pub.concat(var.sTime.t_min);
  sms_pub.concat(",\"SEC\":");
  sms_pub.concat(var.sTime.t_second);
  sms_pub.concat(",\"MAC\":\"");
  sms_pub.concat(var.wifi.Mac);
  sms_pub.concat("\",\"POW_TIME\":");
  sms_pub.concat(0);
  sms_pub.concat(",\"MACHINE_TIME\":");
  sms_pub.concat(0);
  sms_pub.concat(",\"ACT_TIME\":");
  sms_pub.concat(0);
  sms_pub.concat("}");
  MqttClient.publish( topic_pub_Machine_time.c_str(), 2, false, sms_pub.c_str() );
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Mqtt_Client::Pub_Teaching(void)
{
  sms_pub = "";
  sms_pub = "{";
  sms_pub.concat("\"MAC\":\"");
  sms_pub.concat(var.wifi.Mac);
  sms_pub.concat("\",\"PROCESS_ID\":");
  sms_pub.concat(var.Plan.ProcessId);
  sms_pub.concat(",\"MACHINE_TIME\":");
  sms_pub.concat(0);
  sms_pub.concat(",\"ACT_TIME\":");
  sms_pub.concat(0);
  sms_pub.concat("}");
  MqttClient.publish( topic_pub_Teaching.c_str(), 2, false, sms_pub.c_str() );
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Mqtt_Client::Pub_Iot_Status(void)
{
  sms_pub = "";
  if (var.mqtt.Connected == 1)
    sms_pub = MsgIotInfo("ON");
  else
    sms_pub = MsgIotInfo("OFF");
  MqttClient.publish( topic_pub_System.c_str(), 2, false, sms_pub.c_str() );
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}

/************************************************************************************************************************/
void Mqtt_Client::Update_Status(void)
{
  var.mqtt.Connected = MqttClient.connected();
  if (var.mqtt.Connected == 0)
  {
    var.mqtt.Disconnect = 1;
    (var.sTime.Mqtt_Reconnect >= 241) ? (var.sTime.Mqtt_Reconnect = 241) : (var.sTime.Mqtt_Reconnect = var.sTime.Mqtt_Reconnect + 1);
  }
  else
  {
    var.sTime.Mqtt_Reconnect = 0;
    var.mqtt.Disconnect = 0;

  }

}
/************************************************************************************************************************/
void Mqtt_Client::Reconnect(void)
{
  if ( var.wifi.STATUS == 1)
  {
    char s_address[var.mqtt.Address.length()];
    var.mqtt.Address.toCharArray(s_address, var.mqtt.Address.length() + 1);
    MqttClient.setServer(s_address, var.mqtt.Port);
    MqttClient.connect();//dung de ket noi Mqtt
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
    __asm__ __volatile__ ("nop\n\t");
  }
}
/*********************************************************************************************************************/
void Get_Sub_System(String sms)
{
  if (var.sTime.update_finish == 1) return;
  const size_t bufferSize = JSON_OBJECT_SIZE(12) + 500;
  DynamicJsonDocument jsonBuffer(bufferSize);
  jsonBuffer.clear();
  const char* json = sms.c_str();
  DeserializationError error = deserializeJson(jsonBuffer, json);

  if ( error ) return;
  var.sTime.t_year = jsonBuffer["YEAR"];
  var.sTime.t_mon = jsonBuffer["MON"];
  var.sTime.t_day = jsonBuffer["DAY"];
  var.sTime.t_hour = jsonBuffer["HOUR"];
  var.sTime.t_min  = jsonBuffer["MIN"];
  var.sTime.t_second  = jsonBuffer["SEC"];
  var.sTime.info_machine = jsonBuffer["MCINFOTI"];
  setTime(var.sTime.t_hour, var.sTime.t_min, var.sTime.t_second, var.sTime.t_day, var.sTime.t_mon, var.sTime.t_year );
  var.sTime.update_finish = 1;
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Get_Sub_Plan(String sms)
{
  uint8_t plan_size;
  String Factory, Line, Postion, Style, sProcess, ProcessId, WorkerId, Target;
  const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(8) + 350;
  DynamicJsonDocument jsonBuffer(bufferSize);
  jsonBuffer.clear();
  DeserializationError error = deserializeJson(jsonBuffer, sms);
  __asm__ __volatile__ ("nop\n\t");
  if ( error || sms == NULL ) return;
  plan_size = jsonBuffer.size();
  for (uint8_t i = 0; i < plan_size; i++)
  {
    String Factory  = jsonBuffer[i]["FACTORY"];
    var.Plan.Factory = Factory;
    String Line     = jsonBuffer[i]["LINE"];
    var.Plan.Line = Line;
    String Postion  = jsonBuffer[i]["POSITION"];
    var.Plan.Location = Postion;
    String Style    = jsonBuffer[i]["STYLE"];
    var.Plan.Style = Style;
    String sProcess = jsonBuffer[i]["PROCESS"];
    var.Plan.sProcess = sProcess;
    String ProcessId = jsonBuffer[i]["PROCESSID"];
    var.Plan.ProcessId = ProcessId;
    String WorkId   = jsonBuffer[i]["WORKERID"];
    var.Plan.WorkerId = WorkerId;
    String  Target  = jsonBuffer[i]["TARGET"];
    //   var.sensor.target_counter = Target.toInt();
  }
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Get_Sub_Config(String sms)
{
  uint8_t json_size;
  const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 350;
  DynamicJsonDocument jsonBuffer(bufferSize);
  jsonBuffer.clear();
  DeserializationError error = deserializeJson(jsonBuffer, sms);
  __asm__ __volatile__ ("nop\n\t");
  if ( error || sms == NULL ) return;
  json_size = jsonBuffer.size();
  for (uint8_t i = 0; i < json_size; i++)
  {
    String ProcessID  = jsonBuffer[i]["PROCESSID"];
    String Type = jsonBuffer[i]["TYPE"];
    String Data = jsonBuffer[i]["DATA"];
    if ((ProcessID == var.Plan.ProcessId) && (Type == "OUTPUT"))
    {
      // var.sensor.data_counter = Data.toInt();
    }
  }
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Get_Sub_Teaching(String sms)
{
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Get_Sub_Machine_Id(String sms)
{
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 350;
  DynamicJsonDocument jsonBuffer(bufferSize);
  jsonBuffer.clear();
  const char* json = sms.c_str();
  DeserializationError error = deserializeJson(jsonBuffer, json);
  if ( error ) return;
  String id = jsonBuffer["MCID"];
  var.machine.Id = id;
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Get_Sub_Ota(String sms)
{
  const size_t Size = JSON_OBJECT_SIZE(4) + 350;
  DynamicJsonDocument jsonBuffer(Size);
  jsonBuffer.clear();
  const char* data = sms.c_str();
  DeserializationError error = deserializeJson(jsonBuffer, data);
  if (error) return;
  if (jsonBuffer["VER"] == var.lcd.software) return;
  String url_address = jsonBuffer["FLLE"];
  var.ota.url = url_address;
  var.machine.sProcess = PROCESS_OTA_UPDATE;
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
}
/************************************************************************************************************************/
void Mqtt_Client::Get_Sub_UART(String sms)
{
  const size_t Size = JSON_OBJECT_SIZE(7) + 500;
  DynamicJsonDocument jsonBuffer(Size);
  jsonBuffer.clear();
  const char* data = sms.c_str();
  DeserializationError error = deserializeJson(jsonBuffer, data);
  //if(!doc.is<JsonObject>()) kiem tra chuoi khong phai doi tuong Json
  if (sms.length() == 0) return;
  if (error || (!jsonBuffer.is<JsonObject>())) //Khong phai Json
  {
    var.scale.Barcode = sms;
    var.lcd.update_data = 6;
    return;
  }

  String MyPackageGroup = jsonBuffer["PG"];
  uint16_t MyPg_Qty = jsonBuffer["PGQTY"];
  String MyPO = jsonBuffer["BUYER"];
  uint16_t MyPo_Qty = jsonBuffer["POQTY"];
  String MyStyle = jsonBuffer["STYLE"];
  uint16_t MyUnits = jsonBuffer["BOXPCS"];
  String MyUrl = jsonBuffer["IURL"];
  var.scale.PackageGroup = MyPackageGroup;
  var.scale.Pocode = MyPO;
  var.scale.Style_Code = MyStyle;
  var.scale.Units = MyUnits;
  var.scale.Pg_Qty = MyPg_Qty;
  var.scale.Po_Qty = MyPo_Qty;
  var.web.imageUrl = MyUrl;
  var.lcd.update_data = 5;
  var.machine.sProcess = PROCESS_EEP_PO_STYLE_CODE;
}
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
