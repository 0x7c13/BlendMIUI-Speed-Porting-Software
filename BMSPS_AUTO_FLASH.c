
/*
 *  BMSPS_AUTO_FLASH.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  ===== BlendMIUI Speed-Porting Software =====
 *
 *  This is a 100% free software and you can add all kinds
 *  of functions you like to make it powerful and useful.
 *  However,it's intended for personal and/or educational
 *  use only.It may not be duplicated for monetary benefit
 *  or any other purpose without the permission of the developer.
 *
 */



#include <stdio.h>
#include <conio.h>

#include "BMSPS_DEVICE.h"
#include "BMSPS_LANGUAGE.h"

#include "BMSPS_COMMAND_LOG.c"

int WIPE=0; 

int DETECTIVE_DEVICE()   /* if find device return 1 else return 0 */
{
  return COMMAND_LOG("adb get-state","device"); 
}

int DETECTIVE_USB_STORAGE_MODE()   /* if closed return 1 else return 0 */
{
  return COMMAND_LOG("adb shell ls -l /mnt","sdcard_r"); 
}

int PUSH_ROM()   /* if the rom has been pushed return 1 else return 0 */
{ 
  return COMMAND_LOG("adb push update.zip /mnt/sdcard","KB/s");
}

int REBOOT_INTO_FASTBOOT_MODE()   /* if device is under fastboot mode return 1 else return 0 */
{ 
  return COMMAND_LOG("fastboot devices","fastboot");
} 



void REMAINDER(struct BMSPS_LANGUAGE Language)
{
    UI_TOP(Language);    
    DISPLAY("AUTO_FLASH_WARNING",Language);     
    PAUSE();   

    char Option[10];
    int flag=1;     
    
    while(flag)
    {
      UI_TOP(Language);      
      DISPLAY("AUTO_FLASH_WIPE_DATA_AND_CACHE_CHOICE",Language);    
             
      scanf("%s",Option);
      if( strcmp(Option,"yes")== 0)  
        { 
         WIPE=1;  
         flag=0;
        } 
      else if( strcmp(Option,"no")== 0)   flag=0;
    }  
  
}

void CHECK_DEVICE(struct BMSPS_LANGUAGE Language)
{
  UI_TOP(Language);    
  DISPLAY("AUTO_FLASH_OPEN_ADB",Language);  
  system("adb get-state");
  
  while(DETECTIVE_DEVICE()==0)
  {
    UI_TOP(Language);                                    
    DISPLAY("AUTO_FLASH_DETECTIVE_DEVICE_FILED",Language);      
    PAUSE();
  }
  
  while(DETECTIVE_USB_STORAGE_MODE()==0)
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
    system("adb reboot bootloader");    // reboot into fastboot mode
    sleep(5000);
    while(REBOOT_INTO_FASTBOOT_MODE()==0);
}

void FLASH_KERNEL(struct BMSPS_LANGUAGE Language,struct BMSPS_DEVICE Device)
{
    char Command[500]="fastboot flash boot BlendMIUI-kernel\\";
  
    UI_TOP(Language);  
    DISPLAY("AUTO_FLASH_FLASH_KERNEL",Language);  
  
    if( Device.XPERIA_ARC_LT15i || Device.XPERIA_ARC_S_LT18i )   strcat(Command,"Arc\\boot.img");
    if( Device.XPERIA_NEO_MT15i || Device.XPERIA_NEO_V_MT11i )   strcat(Command,"Neo\\boot.img"); 
    if( Device.XPERIA_RAY_ST18i )   strcat(Command,"Ray\\boot.img");     
 
    system(Command);
}

void WIPE_DATA_AND_CACHE(struct BMSPS_LANGUAGE Language)
{
      if( WIPE )  
        {
         UI_TOP(Language);                        
         DISPLAY("AUTO_FLASH_WIPE_DATA_AND_CACHE",Language);  
         system("fastboot -w");    
        } 
}

void REBOOT_INTO_RECOVERY(struct BMSPS_LANGUAGE Language,struct BMSPS_DEVICE Device)
{
    char Command[500]="fastboot boot BMSPS_DATA\\AutoFlash\\AutoFlash-";

    if( Device.XPERIA_ARC_LT15i || Device.XPERIA_ARC_S_LT18i )   strcat(Command,"Arc.img");
    if( Device.XPERIA_NEO_MT15i || Device.XPERIA_NEO_V_MT11i )   strcat(Command,"Neo.img"); 
    if( Device.XPERIA_RAY_ST18i )   strcat(Command,"Ray.img");  
         
    UI_TOP(Language);      
    DISPLAY("AUTO_FLASH_REBOOT_INTO_RECOVERY",Language);     
    system(Command); 
    sleep(5000);

}

void FINISHED(struct BMSPS_LANGUAGE Language)
{
    UI_TOP(Language);     
    DISPLAY("AUTO_FLASH_FINISHED",Language);      
    PAUSE();
    system("taskkill /im adb.exe /t /f > temp_log.txt");
}


void AUTO_FLASH(struct BMSPS_LANGUAGE Language,struct BMSPS_DEVICE Device)
{

   REMAINDER(Language);
         
   CHECK_DEVICE(Language);
    
   PUSH_ROM_TO_SDCARD(Language);
   
   REBOOT_INTO_FASTBOOT(Language);  
   
   FLASH_KERNEL(Language,Device);
     
   WIPE_DATA_AND_CACHE(Language);
   
   REBOOT_INTO_RECOVERY(Language,Device);  
   
   FINISHED(Language);
     
}

