#include "FLASH.h"
//#include "stm32l152xba.h"

#include "..\TIME\time.h"


#define     PELOCK                          1
#define     FTDW                            (1 << 8)



void        Data_EEPROM_Lock (void)                                             //  lock data Flash memory for write 
{
    FLASH->PECR |= PELOCK;                                                      //  set LOCK bit
}


void        Data_EEPROM_Unlock (void)                                           //  unlock data Flash memory for write 
{
    if (FLASH -> PECR & FLASH_PECR_PRGLOCK == 0)
        return;
        
//  Unlocking FLASH_PECR register access
    
    if( FLASH -> PECR & FLASH_PECR_PELOCK != 0)
    {  
         FLASH -> PEKEYR = FLASH_PEKEY1;
         FLASH -> PEKEYR = FLASH_PEKEY2;
    }
    
//  Unlocking the program memory access 
    
    FLASH -> PRGKEYR = FLASH_PRGKEY1;
    FLASH -> PRGKEYR = FLASH_PRGKEY2; 
}


uint16_t    Data_EEPROM_Wait_Until_Ready (uint16_t timeout)                     //  wait until data Flash memory is ready
{
//  z³y parametr, zwróæ fail
    
    if (!timeout)
        return (0);
    
    while ((FLASH->SR & FLASH_FLAG_BSY) && timeout)  {
         Delay_3_ms (2);
         timeout--;
         
    //  timeout, zwróæ fail
         
        if (!timeout)
            return (0);
    }    
        
    return (1);                                                                 //  success
}


void        Data_EEPROM_Program_8b (uint32_t address, uint8_t data)             //  store 8 bit data in data FLash memory
{
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
    Data_EEPROM_Unlock ();                                                      //  unlock memory
    
    FLASH->PECR |= FTDW;                                                        //  set automatic erase mode
    *(__IO uint32_t *) address = data;                                          //  save <Data> into data Flash
    
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
     Data_EEPROM_Lock ();
}


void        Data_EEPROM_Program_16b (uint32_t address, uint16_t data)           //  store 16 bit data in data FLash memory
{
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
    Data_EEPROM_Unlock ();                                                      //  unlock memory
    
    FLASH->PECR |= FTDW;                                                        //  set automatic erase mode
    *(__IO uint32_t *) address = data;                                          //  save <Data> into data Flash
    
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
     Data_EEPROM_Lock ();
}


void        Data_EEPROM_Program_32b (uint32_t address, uint32_t data)           //  store 32 bit data in data FLash memory
{   
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
    Data_EEPROM_Unlock ();                                                      //  unlock memory
    
    FLASH->PECR |= FTDW;                                                        //  set automatic erase mode
    *(__IO uint32_t *) address = data;                                          //  save <Data> into data Flash
    
    Data_EEPROM_Wait_Until_Ready (10);                                          //  wait until memory ready
     Data_EEPROM_Lock ();
}

/*void zones_to_flash ( struct Zones * zone )                                     //copy data from zones structure to flash
{
    uint8_t i;                                                                  //  !!!!!!!!!!!!!!!!!!!!!!! sprawdziæ
    for( i=0;i<7;i++)
    {
        uint32_t data= zone->temp_day[i] + (zone->temp_night[i] << 8) + (zone->time_start[i] << 16) + (zone->time_stop[i]<<24);
        Data_EEPROM_Program_32b ( EEPROM_START_ADDR + (i*4), data);
    }
    
} */


/*void zones_from_flash ( struct Zones * zone )                                   //copy data from flash to zones structure
{
   int i;   

   for( i=0;i<7;i++)
    {
        uint32_t data=*((__IO uint32_t *)( EEPROM_START_ADDR + (i*4)));
       
        zone->temp_day[i] = data & 0xFF;
        
       zone->temp_night[i] = (data>>8) & 0xFF;
        
       zone->time_start[i]= (data>>16) & 0xFF;
        
       zone->time_stop[i] = (data>>24) & 0xFF;
    }
   
}
*/