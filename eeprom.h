#ifndef _epprom_h
#define _epprom_h
#include <EEPROM.h>
#include "interface.h"
class EEPROM_FUNCTION
{
  public:
    void write_setup_teaching(void);
    void write_web_network(void);
    void write_web_server(void);
    void write_web_machine(void);
    void write_web_location(void);
    void write_web_modbus(void);
    void write_setup_monitor(void);
    void write_setup_modbus(void);
    void write_scale_data(void);
    void write_po_code(void);
    void write_style_code(void);
    void write_group_code(void);
    void write_pg_qty(void);
    void write_po_qty(void);
    void write_units_box(void);

    //private:
};
extern EEPROM_FUNCTION    EEP;
#endif
