#include "stdint.h"
//#include "..\Code-ARM\MENU\menu_const.h"

#define     EEPROM_START_ADDR               0x08080000

void        Data_EEPROM_Lock (void);                                            //  lock data Flash memory for write 
void        Data_EEPROM_Unlock (void);                                          //  unlock data Flash memory for write 
uint16_t    Data_EEPROM_Wait_Until_Ready (uint16_t timeout);                    //  wait until data Flash memory is ready

void        Data_EEPROM_Program_8b (uint32_t address, uint8_t data);            //  store 8 bit data in data FLash memory
void        Data_EEPROM_Program_16b (uint32_t address, uint16_t data);          //  store 16 bit data in data FLash memory
void        Data_EEPROM_Program_32b (uint32_t address, uint32_t data);          //  store 32 bit data in data FLash memory

//void zones_to_flash ( struct Zones * zone );                                    //copy data from zones structure to flash
//void zones_from_flash ( struct Zones * zone );                                  //copy data from flash to zones structure