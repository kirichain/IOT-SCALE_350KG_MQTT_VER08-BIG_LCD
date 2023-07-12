#ifndef _interface_h
#define _interface_h


//DEFINE KEYPAD
#define PCF_INT     0// GPIO0 ESP8266

#define KEY_ENTER   2
#define KEY_UP      1
#define IN_SAMPLE   0
#define PCF3        3
#define PCF4        4
#define PCF5        5
#define PCF6        6
#define PCF7        7

#define OK_LAMP1    8 //Out1-OK
#define OK_LAMP     9 //Out2-OK
#define NG_LAMP     10 //Out3-NG
#define SVR_LAMP    11 //Out4-SVR
#define BUZZER      12 //Out5-BUZZER
#define PCF13       13 //

#define PCF14_S1    14//S1
#define PCF15_S0    15//S0

//=======DINH NGHIA CAC TIEN TO
//ADR: ADDRESS
//LCD: LCD OLED
//WIFI: WIFI ESP8266
//MA: MACHINE
//IOT: MODULE IOT
//EVT: EVENT XU KIEN XAY RA
//EEP: EEPROM LUU TRU BO NHO
//TEACH:TEACHING
//SER: SERVER
//SAMPLE: SAMPLE
/***************Define LEN of Variable****************************/
#define EEP_SIZE_INT                             0
#define EEP_SIZE_MQTT_ADDRESS                    16
#define EEP_SIZE_MQTT_PORT                       2
#define EEP_SIZE_MQTT_HTTP_PORT                  2
#define EEP_SIZE_SENSOR_FILTER                   2
#define EEP_SIZE_SENSOR_SDELAY                   1
#define EEP_SIZE_SENSOR_TARGET_COUNTER           2
#define EEP_SIZE_SENSOR_DATA_COUNTER             4
#define EEP_SIZE_SENSOR_INPUT_SAMPLE             2
#define EEP_SIZE_WIFI_SSID                       16
#define EEP_SIZE_WIFI_PASS                       16
#define EEP_SIZE_LCD_ROTATE                      1
#define EEP_SIZE_LCD_CONTRATS                    1
#define EEP_SIZE_LCD_FONTMODE                    1
#define EEP_SIZE_MODBUS_IDSLAVE                  1
#define EEP_SIZE_MODBUS_BAURATE                  1
#define EEP_SIZE_MODBUS_FORMAT                   1
#define EEP_SIZE_SCALE_SAMPLE                    4
#define EEP_SIZE_SCALE_CALLIB                    4
#define EEP_SIZE_SCALE_TOLERANCE_P               1
#define EEP_SIZE_SCALE_TOLERANCE_N               1
#define EEP_SIZE_SCALE_NG_BOX                    2
#define EEP_SIZE_SCALE_OK_BOX                    2
#define EEP_SIZE_PO_CODE                         30
#define EEP_SIZE_STYLE_CODE                      30
#define EEP_SIZE_GROUP_CODE                      30
#define EEP_SIZE_PG_QTY                          2
#define EEP_SIZE_PO_QTY                          2
#define EEP_SIZE_UNIT_BOX                        2

/***************Define Code Address Epprom************************/
#define EEP_ADR_INT                              0
#define EEP_ADR_MQTT_ADDRESS                     EEP_ADR_INT + EEP_SIZE_INT//Server address
#define EEP_ADR_MQTT_PORT                        EEP_ADR_MQTT_ADDRESS + EEP_SIZE_MQTT_ADDRESS + 1
#define EEP_ADR_MQTT_HTTP_PORT                   EEP_ADR_MQTT_PORT + EEP_SIZE_MQTT_PORT + 1
#define EEP_ADR_SENSOR_FILTER                    EEP_ADR_MQTT_HTTP_PORT + +EEP_SIZE_MQTT_HTTP_PORT + 1
#define EEP_ADR_SENSOR_SDELAY                    EEP_ADR_SENSOR_FILTER + EEP_SIZE_SENSOR_FILTER + 1
#define EEP_ADR_SENSOR_TARGET_COUNTER            EEP_ADR_SENSOR_SDELAY + EEP_SIZE_SENSOR_SDELAY + 1
#define EEP_ADR_SENSOR_DATA_COUNTER              EEP_ADR_SENSOR_TARGET_COUNTER + EEP_SIZE_SENSOR_TARGET_COUNTER + 1
#define EEP_ADR_SENSOR_INPUT_SAMPLE              EEP_ADR_SENSOR_DATA_COUNTER + EEP_SIZE_SENSOR_DATA_COUNTER + 1
#define EEP_ADR_WIFI_SSID                        EEP_ADR_SENSOR_INPUT_SAMPLE + EEP_SIZE_SENSOR_INPUT_SAMPLE + 1
#define EEP_ADR_WIFI_PASS                        EEP_ADR_WIFI_SSID + EEP_SIZE_WIFI_SSID + 1
#define EEP_ADR_LCD_ROTATE                       EEP_ADR_WIFI_PASS + EEP_SIZE_WIFI_PASS + 1
#define EEP_ADR_LCD_CONTRATS                     EEP_ADR_LCD_ROTATE + EEP_SIZE_LCD_ROTATE +1
#define EEP_ADR_LCD_FONTMODE                     EEP_ADR_LCD_CONTRATS + EEP_SIZE_LCD_CONTRATS + 1
#define EEP_ADR_MODBUS_IDSLAVE                   EEP_ADR_LCD_FONTMODE + EEP_SIZE_LCD_FONTMODE + 1
#define EEP_ADR_MODBUS_BAURATE                   EEP_ADR_MODBUS_IDSLAVE + EEP_SIZE_MODBUS_IDSLAVE + 1
#define EEP_ADR_MODBUS_FORMAT                    EEP_ADR_MODBUS_BAURATE + EEP_SIZE_MODBUS_BAURATE + 1
#define EEP_ADR_SCALE_SAMPLE                     EEP_ADR_MODBUS_FORMAT + EEP_SIZE_MODBUS_FORMAT + 1
#define EEP_ADR_SCALE_CALLIB                     EEP_ADR_SCALE_SAMPLE + EEP_SIZE_SCALE_SAMPLE + 1
#define EEP_ADR_SCALE_TOLERANCE_P                EEP_ADR_SCALE_CALLIB + EEP_SIZE_SCALE_CALLIB + 1
#define EEP_ADR_SCALE_TOLERANCE_N                EEP_ADR_SCALE_TOLERANCE_P + EEP_SIZE_SCALE_TOLERANCE_P + 1
#define EEP_ADR_SCALE_NG_BOX                     EEP_ADR_SCALE_TOLERANCE_N + EEP_SIZE_SCALE_TOLERANCE_N + 1
#define EEP_ADR_SCALE_OK_BOX                     EEP_ADR_SCALE_NG_BOX + EEP_SIZE_SCALE_NG_BOX + 1
#define EEP_ADR_PO_CODE                          EEP_ADR_SCALE_OK_BOX + EEP_SIZE_SCALE_OK_BOX + 1
#define EEP_ADR_STYLE_CODE                       EEP_ADR_PO_CODE + EEP_SIZE_PO_CODE + 1
#define EEP_ADR_GROUP_CODE                       EEP_ADR_STYLE_CODE + EEP_SIZE_STYLE_CODE + 1
#define EEP_ADR_PG_QTY                           EEP_ADR_GROUP_CODE + EEP_SIZE_GROUP_CODE + 1
#define EEP_ADR_PO_QTY                           EEP_ADR_PG_QTY + EEP_SIZE_PG_QTY + 1
#define EEP_ADR_UNIT_BOX                         EEP_ADR_PO_QTY + EEP_SIZE_PO_QTY + 1

/***************Define Code Function LCD**************************/
#define LCD_PAGE_RUN              0x00
#define LCD_PAGE_STOP             0x01
#define LCD_PAGE_MENU             0x02

#define LCD_PAGE_MENU_TEACHING    0x03
#define LCD_PAGE_MENU_WEB_CONFIG  0x04
#define LCD_PAGE_MENU_SETUP       0x05
#define LCD_PAGE_MENU_INFO        0x06

#define LCD_PAGE_MENU_SETUP_COUNTER     0x07
#define LCD_PAGE_MENU_SETUP_MONITOR     0x08
#define LCD_PAGE_MENU_SETUP_MODBUS      0x09
#define LCD_PAGE_MENU_SETUP_DISPLAY     0x0A

#define LCD_PAGE_MENU_INFO_MACHINE        0x0B
#define LCD_PAGE_MENU_INFO_MACHINE_PLAN   0x0C
#define LCD_PAGE_MENU_INFO_MACHINE_TEACHING 0x0D
#define LCD_PAGE_MENU_INFO_MACHINE_NFC      0x0E

#define LCD_PAGE_MENU_INFO_NETWORK          0x0F
#define LCD_PAGE_MENU_INFO_MODBUS           0x10
#define LCD_PAGE_MACHINE_STOP               0x11

/*************Define Code Process***********************/
#define PROCESS_MQTT_PUB_SCALE                  0x00
#define PROCESS_MQTT_PUB_MACHINE_TIME           0x01
#define PROCESS_MQTT_PUB_TEACHING               0x02
#define PROCESS_MQTT_PUB_STATUS                 0x03
#define PROCESS_MQTT_RECONNECT                  0x04
#define PROCESS_CONTROLL_LED                    0x05

#define PROCESS_WEB_SERVER_CONFIG               0x06
#define PROCESS_EEP_MENU_TEACHING               0x07
#define PROCESS_EEP_WEB_NETWORK                 0x08
#define PROCESS_EEP_WEB_SERVER                  0x09
#define PROCESS_EEP_WEB_SERVER_PORT             0x0A
#define PROCESS_EEP_WEB_HTTP_PORT               0x0B
#define PROCESS_EEP_SETUP_LCD                   0X0C
#define PROCESS_EEP_SETUP_MONITOR               0x0D
#define PROCESS_EEP_SETUP_MODBUS                0x0E
#define PROCESS_OTA_UPDATE                      0x0F
#define PROCESS_SCALE_ZERO                      0x10
#define PROCESS_EEP_SCALE_DATA                  0x11
#define PROCESS_SCALE_SAMPLE                    0x12
#define PROCESS_WIFI_RECONNECT                  0x13
#define PROCESS_EEP_PO_CODE                     0x14
#define PROCESS_EEP_PO_STYLE_CODE               0x15
#define PROCESS_OK_LAMP                         0x16
#define PROCESS_NG_LAMP                         0x17
#define PROCESS_NONE_LAMP                       0x18

#define PROCESS_ESP_RESET                       0xF0
#define PROCESS_EMPTY                           0xFF
/********************************DEFINE CODE************************************/
#define CMD_I2C_REQUES_SAMPLE                          0x01
#define CMD_I2C_REQUES_WEIGHT                          0x02
#define CMD_I2C_REQUES_DATA                            0x03
#define CMD_I2C_REQUES_INFO                            0x04
#define CMD_I2C_SEND_INFO                              0x05
#define CMD_I2C_SEND_WEIGHT                            0x06
#define CMD_I2C_SEND_PCS                               0X07
#define CMD_I2C_EMPTY                                  0XFF

typedef struct PLAN {
    String Country = "-";
    String Factory = "-";
    String Line = "-";
    String Location = "-";
    String Style = "-";
    String sProcess = "-";
    String ProcessId = "---";
    String WorkerId = "-";
} PLAN;
/************************************************************************************************************************/
typedef struct OTA {
    String url = "-";
} OTA;
/************************************************************************************************************************/
//Cau truc bien cua he thong
typedef struct TIME {
    bool Int1 = 0;
    bool Int2 = 0;
    uint16_t t_year;
    uint8_t t_mon;
    uint8_t t_day;
    uint8_t t_hour;
    uint8_t t_min;
    uint8_t t_second;
    uint8_t t_old = 0;

    uint8_t Mqtt_Reconnect = 0;
    uint16_t Mqtt_Status = 0;
    uint16_t Machine_Time = 0;

    uint16_t info_machine;
    uint16_t Cycle = 0;
    bool update_finish = 0;
} TIME;

//cau truc bien can cua LCD
typedef struct LCD {
    uint8_t old_y_postion = 1;
    uint8_t y_postion = 0;
    String hardware;
    String software;
    uint8_t page = 0;
    uint8_t old_page = 1;
    uint8_t rotate = 1;
    uint8_t contrats;
    uint8_t code_monitor = 0;
    bool fontmode = 0;
    bool Fresh = 0;
    //bool      Menu_Up = 0;
    uint8_t update_data = 0;
} LCD;
/************************************************************************************************************************/
//cau truc bien can cua WIFI
typedef struct WIFI {
    bool STATUS;
    String ssid = "Guest";
    String pass = "24091995";
    char eepSsid[16];
    char eepPass[16];
    uint8_t Strenght;
    uint8_t Old_Strenght = 0;
    uint8_t Reconnect_count = 0;
    String Mac = "";
    String Mac_Ap = "";
} WIFI;
/************************************************************************************************************************/
//cau truc bien can cua MQTT
typedef struct MQTT {
    String Address;
    char Array[16];
    uint16_t Port;
    uint16_t httpPort;
    bool Connected;
    bool Disconnect = 0;
} MQTT;
/************************************************************************************************************************/
//cau truc bien can cua SERVER
typedef struct WEB {
    String codeHmi = "";
    String codeSuccess = "";
    String codeFail = "";
    String codeReset = "";
    String imageUrl = "";
    bool STATUS;
    bool Config = 0;
    // Array to store the image, image size is 100x100
    uint16_t imageArray[10000] = {0};
    // Array to store the image, image size is 120x120
    //uint16_t imageArray[14400] = {0};
    //char serverUrl[100] = "http://64a77ed6096b3f0fcc815dc3.mockapi.io/api/8bit/";
    //char _serverUrl[100] = "http://64a77ed6096b3f0fcc815dc3.mockapi.io/api/8bit/";
    //char filename[10] = "arr";
    char serverUrl[100] = "http://10.102.40.171:80/ProcessImage/GetDataImage";
    char _serverUrl[100] = "http://10.102.40.171:80/ProcessImage/GetDataImage";
    char filename[10] = "";
} WEB;
/************************************************************************************************************************/
//cau truc bien can cua MACHINE STATUS
typedef struct MACHINE {
    bool status_wifi;
    uint8_t sProcess = PROCESS_EMPTY; //code process action
    uint8_t Old_sProcess;
    uint8_t sProcess_menu;//code
    String Ip;//Address machine IP
    String Id;//Address machine ID
    String Iot_code;//code machine Supplier
    String Iot_model;//Model Iot
} MACHINE;
/************************************************************************************************************************/
typedef struct LOAD {
    bool pStatus = 0;
    bool Change_Status;
} LOAD;
/************************************************************************************************************************/
//cau truc bien can cua MODBUS RTU
typedef struct MODBUS_RTU {
    bool Status = 0;//Trang Thai On cua modbus
    uint8_t IDslave = 1;
    uint8_t Baurate;
    uint8_t Format;
    uint16_t Sv_Data = 75;
    uint16_t Pv_Data = 30;
    uint16_t Sv_Adr;
    uint16_t Pv_Adr;
} MODBUS_RTU;
/************************************************************************************************************************/
//cau truc du lieu SENSOR
typedef struct SENSOR_SCALE {
    char eep_po[30];
    char eep_style[30];
    char eep_group[30];
    String Barcode = "NONE";
    String Pocode = "NONE";
    String Style_Code = "NONE";
    String PackageGroup = "NONE";
    String st_weight_old = "0.00";
    bool Status = 0; //1 Error, 0 OK
    bool Pub = 0; //1 pub du lieu, 0 ko pub du lieu
    bool Check_begin = 0;
    bool Check_end = 0;
    bool Check = 0;//ung de kiem doc gia tri Weight_old
    bool pause_max = 0;//pause read Weight_max
    uint8_t Tolerance_p = 0; //Sai so cho phep duong
    uint8_t Tolerance_n = 0; //Sai so cho phep am
    uint8_t Box;
    uint8_t Box_max;
    uint8_t Counter = 0;
    uint8_t Pause_counter = 0;
    uint16_t Ok_Box = 0;
    uint16_t Ng_Box = 0;
    uint16_t Sum_box = 0;
    uint16_t Units = 1;
    uint16_t Pg_Qty = 0;
    uint16_t Po_Qty = 0;
    uint32_t old_time = 0;
    float Weight = 0;
    float Weight_old = 0;
    float Weight_max = 0;
    float Sample = 99;
    float delta = 0;
} SENSOR_SCALE;
/************************************************************************************************************************/
//khai bao toan bo cau truc
typedef struct {
    struct PLAN Plan;
    struct OTA ota;
    struct TIME sTime;
    struct LCD lcd;
    struct WIFI wifi;
    struct MQTT mqtt;
    struct WEB web;
    struct MACHINE machine;
    struct MODBUS_RTU rtu;
    struct SENSOR_SCALE scale;
    struct LOAD sload;
} var_all;
/************************************************************************************************************************/
extern var_all var;
#endif
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/
