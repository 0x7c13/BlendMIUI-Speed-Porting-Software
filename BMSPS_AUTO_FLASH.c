
/*
 *  BMSPS_AUTO_FLASH.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  ===== BlendMIUI Speed-Porting Software =====
 *
 *  This is 100% free software and you can add all kinds
 *  of functions you like to make it powerful and useful
 *  to use.However,it's intended for personal and/or
 *  educational use only.It may not be duplicated for monetary
 *  benefit or any other purpose without the permission of the developer.
 *
 */



#include <stdio.h>
#include <conio.h>

#include "BMSPS_DEVICE.h"
#include "BMSPS_LANGUAGE.h"

#include "BMSPS_COMMAND_LOG.c"
#include "BMSPS_PUSH_ROM.c"
#include "BMSPS_DETECTIVE_DEVICE.c"
#include "BMSPS_REBOOT_INTO_FASTBOOT_MODE.c"
#include "BMSPS_DETECTIVE_USB_STORAGE_MODE.c"



void CHECK_DEVICE(struct BMSPS_LANGUAGE Language)
{
  
  while(DETECTIVE_DEVICE()==0)
  {
    UI_TOP(Language);                                    
    DISPLAY("AUTO_FLASH_DETECTIVE_DEVICE_FILED",Language);      
    PAUSE();                            
  }
  
  while(DETECTIVE_USB_STORAGE_MODE())
  {
    UI_TOP(Language);                                    
    DISPLAY("AUTO_FLASH_DETECTIVE_USB_STORAGE_MODE_FILED",Language);      
    PAUSE();                            
  }   
    
}

void PUSH_ROM_TO_SDCARD(struct BMSPS_LANGUAGE Language)
{
    UI_TOP(Language);                                    
    DISPLAY("AUTO_FLASH_PUSH_ROM_TO_SDCARD",Language); 
    PUSH_ROM();
}

void REBOOT_INTO_FASTBOOT(struct BMSPS_LANGUAGE Language)
{
    UI_TOP(Language);         
    DISPLAY("AUTO_FLASH_REBOOT_INTO_FASTBOOT_MODE",Language);       
    system("adb reboot bootloader");  
    while(REBOOT_INTO_FASTBOOT_MODE()==0);
}

void FLASH_KERNEL(struct BMSPS_LANGUAGE Language,struct BMSPS_DEVICE Device)
{
    char Command[500]="fastboot flash boot BlendMIUI-kernel\\";
  
    UI_TOP(Language);  
    DISPLAY("AUTO_FLASH_FLASH_KERNEL",Language);  
  
    if( Device.XPERIA_ARC_LT15i || Device.XPERIA_ARC_S_LT18i)   strcat(Command,"Arc\\boot.img");
    if( Device.XPERIA_NEO_MT15i )   strcat(Command,"Neo\\boot.img"); 
    if( Device.XPERIA_RAY_ST18i )   strcat(Command,"Ray\\boot.img");     
 
    system(Command);
}

void WIPE_DATA_AND_CACHE(struct BMSPS_LANGUAGE Language)
{
    char Option[10];
    int flag=1;     
    
    while(flag)
    {
      UI_TOP(Language);      
      DISPLAY("AUTO_FLASH_WIPE_DATA_AND_CACHE_CHOICE",Language);    
             
      scanf("%s",Option);
      if( strcmp(Option,"yes")== 0)  
        {
         UI_TOP(Language);                        
         DISPLAY("AUTO_FLASH_WIPE_DATA_AND_CACHE",Language);  
         system("fastboot -w");    
         flag=0;
        } 
      else if( strcmp(Option,"no")== 0)   flag=0;
    }
         
}

void REBOOT_INTO_RECOVERY(struct BMSPS_LANGUAGE Language)
{
    system("fastboot reboot");
         
    UI_TOP(Language);      
    
    DISPLAY("AUTO_FLASH_REBOOT_INTO_RECOVERY",Language);    
     
    sleep(25000);
 
    system("adb shell \"reboot recovery\"");
    
    sleep(20000);

}

void FINISHED(struct BMSPS_LANGUAGE Language)
{
    UI_TOP(Language);     
    DISPLAY("AUTO_FLASH_FINISHED",Language);      
    getch();
}


void AUTO_FLASH(struct BMSPS_LANGUAGE Language,struct BMSPS_DEVICE Device)
{
     
   CHECK_DEVICE(Language);
    
   PUSH_ROM_TO_SDCARD(Language);
   
   REBOOT_INTO_FASTBOOT(Language);  
   
   FLASH_KERNEL(Language,Device);
     
   WIPE_DATA_AND_CACHE(Language);
   
   REBOOT_INTO_RECOVERY(Language);  
   
   FINISHED(Language);
     
}

