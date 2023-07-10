#include <arduino.h>
#include "web.h"
#include "interface.h"


WiFiClient client;
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

// function downloadImgData with params: (String url, String filename)
bool downloadImgData(String url, String filename) {
    Serial.println("Downloading image data...");
    Serial.println("URL: " + url);
    Serial.println("Filename: " + filename);
    return true;
}

void NOT_FOUND_API(void)
{
  String sms = "File Not Found\n\n";
  sms += "URI: ";
  sms += httpServer.uri();
  sms += "\nMethod: ";
  sms += (httpServer.method() == HTTP_GET) ? "GET" : "POST";
  sms += "\nArguments: ";
  sms += httpServer.args();
  sms += "\n";
  for (uint8_t i = 0; i < httpServer.args(); i++)
  {
    sms += " " + httpServer.argName(i) + ": " + httpServer.arg(i) + "\n";
  }
  httpServer.send(404, "text/plain", sms);
}
/************************************************************************************************************************/
void handleRoot(void)
{
  String header = "HTTP/1.1 301 OK\r\nLocation:/pk2_web_config\r\nCache-Control: no-cache\r\n\r\n";
  httpServer.sendContent(header);
}
/************************************************************************************************************************/
void data_web_config(void)
{
  uint8_t submit_code = 0xff;
  if ( httpServer.hasArg("SUBMIT_NET") )
  {
    if (Submit_Network())
    {
      submit_code = 1;
      var.machine.sProcess_menu = PROCESS_EEP_WEB_NETWORK;
    }
    else submit_code = 0;
  }
  else if (httpServer.hasArg("SUBMIT_SERVER"))
  {
    if (Submit_Server())
    {
      submit_code = 1;
      var.machine.sProcess_menu = PROCESS_EEP_WEB_SERVER;
    }
    else
      submit_code = 0;
  }

  else if ( httpServer.hasArg("FINISH") )
  {
    submit_code = 2;
  }
  switch (submit_code)
  {
    case 0:
      httpServer.sendContent(var.web.codeFail);
      break;
    case 1:
      httpServer.sendContent(var.web.codeSuccess);
      break;
    case 2:
      httpServer.sendContent(var.web.codeReset);
      __asm__ __volatile__ ("nop\n\t");
      __asm__ __volatile__ ("nop\n\t");
      __asm__ __volatile__ ("nop\n\t");
      __asm__ __volatile__ ("nop\n\t");
      var.machine.sProcess_menu = PROCESS_ESP_RESET;
      ESP.reset();
      break;
    default:
      break;
  }
  web.Creat_Hmi();
  httpServer.sendContent( var.web.codeHmi);
}
/************************************************************************************************************************/
bool Submit_Network(void)
{
  String SSID = httpServer.arg("SSID");
  if (SSID)
  {
    var.wifi.ssid = SSID;
  }
  else return false;
  String PASSWORD = httpServer.arg("PASSWORD");
  if (PASSWORD)
  {
    var.wifi.pass = PASSWORD;
  }
  else return false;
  return true;
}
/************************************************************************************************************************/
bool Submit_Server(void)
{
  String address_server = httpServer.arg("ADDRESS_SERVER");
  if (address_server)
  {
    var.mqtt.Address = address_server;
  }
  else return false;
  String http_port = httpServer.arg("SERVER_PORT");
  if (http_port)
  {
    var.mqtt.httpPort = http_port.toInt();
  }
  else return false;
  return true;

}
/************************************************************************************************************************/
bool Submit_Location(void)
{
  String Country = httpServer.arg("COUNTRY");
  if (Country)
  {
    var.Plan.Country = Country;
  }
  else return false;
  String Factory = httpServer.arg("FACTORY");
  if (Factory)
  {
    var.Plan.Factory = Factory;
  }
  else return false;
  String Line = httpServer.arg("LINE");
  if (Line)
  {
    var.Plan.Line = Line;
  }
  else return false;
  String Location = httpServer.arg("LOCATION");
  if (Location)
  {
    var.Plan.Location = Location;
  }
  else return false;
  return true;
}
/************************************************************************************************************************/
bool Submit_Machine(void)
{
  return 1;
}
/************************************************************************************************************************/
bool Submit_Modbus(void)
{
  return 1;
}
/************************************************************************************************************************/
void web_function::Setup_Http(void)
{
  httpUpdater.setup(&httpServer);//used to OTA
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

  httpServer.onNotFound(NOT_FOUND_API);  //called when handler is not assigned
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

  httpServer.begin();
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

}
/************************************************************************************************************************/
void web_function::Setup_Web(void)
{
  String AP_SSID = String("DAQC-PK2-") + var.wifi.Mac;
  String AP_KEY_PASS = "123456789";
  WiFi.disconnect(true);
  // WiFi.enableSTA(0);
  WiFi.enableAP(1);
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(AP_SSID.c_str(), AP_KEY_PASS.c_str());
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

  httpServer.on("/", handleRoot);//void on(const String &uri, THandlerFunction handler);
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

  httpServer.on("/pk2_web_config", data_web_config);//void on(const String &uri, THandlerFunction handler);
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");
  __asm__ __volatile__ ("nop\n\t");

}
/************************************************************************************************************************/
void web_function::handle_Client(void)
{
  httpServer.handleClient();
}
/************************************************************************************************************************/
void web_function::Ota(void)
{
  String Ota_url = String("http://") + var.mqtt.Address + ":" + String(var.mqtt.httpPort) + "/" + var.ota.url;
  ESPhttpUpdate.update(client, Ota_url);
}
/************************************************************************************************************************/
void web_function::Creat_Hmi(void)
{
  var.web.codeHmi = R"(
  <html>
  <head>
  <meta charset="utf-8"><title>DAQC_Web_Config</title>
  <style> 
  .tab{overflow: hidden;border: 1px solid #ccc;background-color: #00cc66;}
  .tab input{background-color: inherit;float:left;border: none;outline: none;cursor: pointer;padding: 14px 16px; transition: 0.3s;font-size: 17px }
  .tab input:hover{background-color: #ddd;}
  .tab input.active{background-color: #ccc}
  .tabcontent{display: none;padding:6px 12px;border: 1px solid#ccc;border-top: none;}
  </style></head>)";

  var.web.codeHmi += R"(<body><p><h2 style="text-align: center; color:#0066ff">IOT-DAQC WEB CONFIG.</h2></p>)";
  var.web.codeHmi += "<div class=\"tab\">";
  var.web.codeHmi += "<input type=\"button\" class=\"tablinks\" onclick=\"openType(event,'Network')\" value=\"NETWORK\">";
  var.web.codeHmi += "<input type=\"button\" class=\"tablinks\" onclick=\"openType(event,'Server')\" value=\"SERVER\">";
  var.web.codeHmi += "<input type=\"button\" class=\"tablinks\" onclick=\"openType(event,'Location')\" value=\"LOCATION\">";
  var.web.codeHmi += "<input type=\"button\" class=\"tablinks\" onclick=\"openType(event,'Machine')\" value=\"MACHINE\">";
  var.web.codeHmi += "<input type=\"button\" class=\"tablinks\" onclick=\"openType(event,'ModbusRtu')\" value=\"MODBUS-RTU\">";
  var.web.codeHmi += "</div>"; //end menu

  var.web.codeHmi += "<div id =\"Network\" class=\"tabcontent\"><h3 style=\"color:#0066ff\"><i>NETWORK SETUP.</i></h3>";
  var.web.codeHmi += "<form method=\"post\" action=\"/pk2_web_config\">";
  var.web.codeHmi += "<table>";
  var.web.codeHmi += "<tr><td>SSID :</td><td><input type=\"text\"name=\"SSID\" maxlength=\"16\" value=\"" + var.wifi.ssid + "\"></td></tr>";
  var.web.codeHmi += "<tr><td>PassWord:</td><td><input type=\"text\"name=\"PASSWORD\" maxlength=\"16\" value=\"" + var.wifi.pass + "\"></td></tr>";
  var.web.codeHmi += "</table>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<input name=\"SUBMIT_NET\"type=\"submit\"value=\"Submit\">";
  var.web.codeHmi += "</form>";
  var.web.codeHmi += "</div>";//end tab NETWORK SETUP

  var.web.codeHmi += "<div id = \"Server\" class = \"tabcontent\"><h3 style = \"color: #0066ff\"><i>SERVER SETUP. </i></h3>";
  var.web.codeHmi += "<form method = \"post\" action = \"/pk2_web_config\">";
  var.web.codeHmi += "<table>";
  var.web.codeHmi += "<tr><td>Address Server:</td><td><input type = \"text\" name = \"ADDRESS_SERVER\" maxlength = \"16\" value =\"" + var.mqtt.Address + "\"></td></tr>";
  var.web.codeHmi += "<tr><td>Server Port:</td><td><input type = \"number\" name = \"SERVER_PORT\" maxlength = \"6\" value = \"" + String(var.mqtt.httpPort) + "\"></td></tr>";
  var.web.codeHmi += "</table>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<input name =\"SUBMIT_SERVER\" type =\"submit\" value = \"Submit\">";
  var.web.codeHmi += "</form>";
  var.web.codeHmi += "</div>";//end tab SERVER

  var.web.codeHmi += "<div id = \"Location\" class = \"tabcontent\"><h3 style = \"color: #0066ff\"><i>LOCATION SETUP .</i></h3>";
  var.web.codeHmi += "<form method = \"post\" action = \"/pk2_web_config\">";
  var.web.codeHmi += "<table>";
  var.web.codeHmi += "<tr><td>Country:</td><td><input type = \"text\" name = \"COUNTRY\" maxlength = \"10\" value = \"" + var.Plan.Country + "\"></td></tr>";
  var.web.codeHmi += "<tr><td>Factory:</td><td><input type = \"text\" name = \"FACTORY\" maxlength = \"10\" value = \"" + var.Plan.Factory + "\"></td></tr>";
  var.web.codeHmi += "<tr><td>Line:</td><td><input type = \"text\" name = \"LINE\" maxlength = \"10\" value = \"" + var.Plan.Line + "\"></td></tr>";
  var.web.codeHmi += "<tr><td>Location:</td><td><input type = \"text\" name = \"LOCATION\" maxlength=\"10\" value=\"" + var.Plan.Location + "\"></td></tr>";
  var.web.codeHmi += "</table>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<input name = \"SUBMIT_LOCATION\" type = \"submit\" value = \"Submit\">";
  var.web.codeHmi += "</form>";
  var.web.codeHmi += "</div>"; //end tab LOCATION

  var.web.codeHmi += "<div id = \"Machine\" class = \"tabcontent\"><h3 style = \"color: #0066ff\"><i>MACHINE SETUP.</i></h3>";
  var.web.codeHmi += "<form method = \"post\" action = \"/pk2_web_config\">";
  var.web.codeHmi += "<table>";
  var.web.codeHmi += "<tr><td>Suplier:</td ><td><input type = \"text\" name = \"SUPLIER\" maxlength = \"10\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Target:</td><td><input type = \"number\" name = \"TARGET\" maxlength = \"10\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>PPC:</td><td><input type = \"number\" name = \"PPC\" maxlength = \"10\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Process ID:</td><td><input type = \"text\" name = \"PROCESSID\"></td></tr>";
  var.web.codeHmi += "</table>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<input name = \"SUBMIT_MACHINE\" type = \"submit\" value = \"Submit\">";
  var.web.codeHmi += "</form>";
  var.web.codeHmi += "</div>"; //end tab MACHINE

  var.web.codeHmi += "<div id = \"ModbusRtu\" class = \"tabcontent\"><h3 style = \"color: #0066ff\"><i>MODBUS SETUP.</i></h3>";
  var.web.codeHmi += "<form method = \"post\" action = \"/pk2_web_config\">";
  var.web.codeHmi += "<table>";
  var.web.codeHmi += "<tr><td>Address Slave:</td><td><input type = \"number\" name = \"address_slave\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Baud Rate:</td><td><input type = \"number\" name = \"Baudrate\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Format Modbus:</td><td><input type = \"number\" name = \"Format_modbus\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Address Data1:</td><td><input type = \"number\" name = \"Address_data1\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Address Data2:</td><td><input type = \"number\" name = \"Adress_data2\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Address Data3:</td><td><input type = \"number\" name = \"Address_data3\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "<tr><td>Address Data4:</td><td><input type = \"number\" name = \"Address_data4\" maxlength = \"6\" value = \"\"></td></tr>";
  var.web.codeHmi += "</table>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<br>";
  var.web.codeHmi += "<input name = \"SUBMIT_MODBUS\" type = \"submit\" value = \"Submit\">";
  var.web.codeHmi += "</form>";
  var.web.codeHmi += "</div>"; //end tab Modbus

  var.web.codeHmi += R"(<script>
             function add_fields()
             {
          var inputVal = document.getElementById("edt_value").value;
          var objTo = document.getElementById('room_fileds');
          var divtest = document.createElement("div");
          divtest.innerHTML = '<br><div><input type="text" style="border:0; width:48px;" value="' + selectVal + '"/><input type="number" style="width:70px;" name="' + selectVal + '" value="' + inputVal + '" /></div>';
          objTo.appendChild(divtest);
             }
    function openType(evt, typeName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
      tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
      tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(typeName).style.display = "block";
    evt.currentTarget.className += " active";
  }
  </script ><br>
  <br>
  <form method = "post"><input type = "submit" name = "FINISH" value = "Finish"></form >
  </body></html>)";
  var.web.codeSuccess = R"(<html><body><script>alert("Submit SUCCESS!!!");</script></body></html>)";
  var.web.codeFail = R"(<html><body><script>alert("Submit FAIL!!!");</script></body></html>)";
  var.web.codeReset = R"(<html><body><script>alert("Web Config Finish!!ESP_RESET!");</script></body></html>)";
}

/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
