#include <Arduino.h>
#include "eeprom.h"


/************************************************************************/
//Function EEPROM write data teaching
void EEPROM_FUNCTION::write_setup_teaching(void)
{
  EEPROM.put(EEP_ADR_SCALE_SAMPLE, var.scale.Sample);
  EEPROM.put(EEP_ADR_SCALE_TOLERANCE_P, var.scale.Tolerance_p);
  EEPROM.put(EEP_ADR_SCALE_TOLERANCE_N, var.scale.Tolerance_n);
  EEPROM.commit();
}
/************************************************************************/
//Function EEPROM write data network
void EEPROM_FUNCTION::write_web_network(void)
{
  String ssid = var.wifi.ssid;
  String pass = var.wifi.pass;
  ssid.toCharArray(var.wifi.eepSsid, ssid.length() + 1);
  pass.toCharArray(var.wifi.eepPass, pass.length() + 1);
  EEPROM.put(EEP_ADR_WIFI_SSID, var.wifi.eepSsid);
  EEPROM.put(EEP_ADR_WIFI_PASS, var.wifi.eepPass);
  EEPROM.commit();

}
/************************************************************************/
//Function EEPROM write data server
void EEPROM_FUNCTION::write_web_server(void)
{
  char mqtt_address[16];
  (var.mqtt.Address).toCharArray(mqtt_address, (var.mqtt.Address).length() + 1);
  EEPROM.put(EEP_ADR_MQTT_ADDRESS, mqtt_address);
  EEPROM.put(EEP_ADR_MQTT_HTTP_PORT, var.mqtt.httpPort);
  EEPROM.commit();
}
/************************************************************************/
//Function EEPROM write setup monitor
void EEPROM_FUNCTION::write_setup_monitor(void)
{
  EEPROM.put(EEP_ADR_LCD_CONTRATS, var.lcd.contrats);
  EEPROM.put(EEP_ADR_LCD_ROTATE, var.lcd.rotate);
  if (var.lcd.fontmode = 0)
    EEPROM.put(EEP_ADR_LCD_FONTMODE, 0);
  else EEPROM.put(EEP_ADR_LCD_FONTMODE, 255);
  EEPROM.commit();
}
/************************************************************************/
//Function EEPROM write setup monitor
void EEPROM_FUNCTION::write_setup_modbus(void)
{
  EEPROM.put(EEP_ADR_MODBUS_IDSLAVE, var.rtu.IDslave);
  EEPROM.put(EEP_ADR_MODBUS_BAURATE, var.rtu.Baurate);
  EEPROM.put(EEP_ADR_MODBUS_FORMAT, var.rtu.Format);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_scale_data(void)
{
  EEPROM.put(EEP_ADR_SCALE_OK_BOX, var.scale.Ok_Box);
  EEPROM.put(EEP_ADR_SCALE_NG_BOX, var.scale.Ng_Box);
  EEPROM.commit();

}

/************************************************************************/
void EEPROM_FUNCTION::write_po_code(void)
{
  String po = var.scale.Pocode;
  po.toCharArray(var.scale.eep_po, po.length() + 1);
  EEPROM.put(EEP_ADR_PO_CODE, var.scale.eep_po);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_style_code(void)
{
  String style = var.scale.Style_Code;
  style.toCharArray(var.scale.eep_style, style.length() + 1);
  EEPROM.put(EEP_ADR_STYLE_CODE, var.scale.eep_style);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_group_code(void)
{
  String style = var.scale.PackageGroup;
  style.toCharArray(var.scale.eep_group, style.length() + 1);
  EEPROM.put(EEP_ADR_GROUP_CODE, var.scale.eep_group);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_pg_qty(void)
{
  EEPROM.put(EEP_ADR_PG_QTY, var.scale.Pg_Qty);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_po_qty(void)
{

  EEPROM.put(EEP_ADR_PO_QTY, var.scale.Po_Qty);
  EEPROM.commit();
}
/************************************************************************/
void EEPROM_FUNCTION::write_units_box(void)
{

  EEPROM.put(EEP_ADR_UNIT_BOX, var.scale.Units);
  EEPROM.commit();
}
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
