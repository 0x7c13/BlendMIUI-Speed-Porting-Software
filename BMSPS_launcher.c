
/*
 *  BMSPS_launcher.c
 *  Created on: 11-25-2011
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

#define BMSPS_VERSION V05.0

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#include "BMSPS_LANGUAGE.h"
#include "BMSPS_DEVICE.h"
#include "BMSPS_ADDONS.h"

#include "BMSPS_BASIC_FUNCTIONS.c"
#include "BMSPS_UI_PRINT.c"
#include "BMSPS_FIND_IN_FILE.c"
#include "BMSPS_AUTO_FLASH.c"


struct BMSPS_LANGUAGE Language;
struct BMSPS_DEVICE Device;
struct BMSPS_ADDONS Addon;


void CLEAN_WORKSPACE()
{
  /* Clean */   
  DELETE_DIC("META-INF");  
  DELETE_DIC("system");
  DELETE_FILE("mnt_log.txt");
  DELETE_FILE("temp_log.txt");   
  DELETE_FILE("boot.img");
  DELETE_FILE("temp.zip");
  DELETE_FILE("build.prop");
  system("taskkill /im adb.exe /t /f > temp_log.txt");  
  /* Clean */       
}


void SETUP_WORKSPACE()
{
     
  /* set defult value */   
  Language.English=0;
  Language.Chinese=0;
  
  Device.XPERIA_ARC_LT15i=0;
  Device.XPERIA_ARC_S_LT18i=0;
  Device.XPERIA_NEO_MT15i=0;
  Device.XPERIA_NEO_V_MT11i=0;  
  Device.XPERIA_RAY_ST18i=0; 
  Device.XPERIA_PLAY_R800i=0;   
  
  Addon.BlendUI=0;
  Addon.DSPManager=0;
  Addon.SE_Media=0;
  Addon.Tweaks=0;
  /* set defult value */    
  
  CLEAN_WORKSPACE();        
}


void CHOSE_LANGUAGE()
{
  int flag=1,Option;
   
  while(flag)
  {   
     system("CLS"); 
     HideCursor();      
     
     DISPLAY("CHOSE_LANGUAGE",Language);   
  
     Option=(getchar()-'0');
     if ( Option==1 || Option==2 )  flag=0;
  } 

  switch(Option)
   {
      case 1: { Language.English=1; break;}
      case 2: { Language.Chinese=1; break;}
   }

}


void DESCRIPTION()
{
  UI_TOP(Language);   
  
  DISPLAY("DESCRIPTION",Language);
  
  PAUSE();
}


int CHOSE_DEVICE_CONFIRM(int Choice)
{
  char Option[10];
  
  while(1)
   {  
      UI_TOP(Language);
      DISPLAY("CHOSE_DEVICE_CONFIRM_1",Language);   
      
      if      ( Choice==1 )    puts("XPERIA ARC LT15i\n");
      else if ( Choice==2 )    puts("XPERIA ARC S LT18i\n");
      else if ( Choice==3 )    puts("XPERIA NEO MT15i\n"); 
      else if ( Choice==4 )    puts("XPERIA NEO V MT11i\n");     
      else if ( Choice==5 )    puts("XPERIA RAY ST18i\n");  
      else if ( Choice==6 )    puts("XPERIA PLAY R800i\n");   
        
      DISPLAY("CHOSE_DEVICE_CONFIRM_2",Language);    
       
      scanf("%s",Option);
       
     if ( strcmp(Option,"yes")==0 || strcmp(Option,"YES")==0 )      return 1;
     else if ( strcmp(Option,"no")==0 || strcmp(Option,"NO")==0 )   return 0;
   }       
     
}


void CHOSE_DEVICE()
{
  int flag=1,Option;
  
  while(flag)
   {  
     UI_TOP(Language); 
                
     DISPLAY("CHOSE_DEVICE",Language); 
     
     Option=(getchar()-'0');
     
     if ( Option==1 || Option==2 || Option==3 || Option==4 || Option==5 || Option==6 )  
     {         
        if( CHOSE_DEVICE_CONFIRM(Option) )  flag=0;
     }   
   }
   
  switch(Option)
   {
      case 1: { Device.XPERIA_ARC_LT15i=1;   break;}
      case 2: { Device.XPERIA_ARC_S_LT18i=1; break;}
      case 3: { Device.XPERIA_NEO_MT15i=1;   break;}      
      case 4: { Device.XPERIA_NEO_V_MT11i=1; break;}        
      case 5: { Device.XPERIA_RAY_ST18i=1;   break;} 
      case 6: { Device.XPERIA_PLAY_R800i=1;  break;}       
   }
}

void MIUI_ROM_CHECK()
{
     while(FILE_CHECK("MIUI_DHD_ROM\\MIUI.zip")==0)
     {
       UI_TOP(Language);    
       
       DISPLAY("MIUI_ROM_CHECK",Language);             
                   
       PAUSE();                              
     }
}

void SHOW_PROGRESS(Step)
{
   int i;
   
   UI_TOP(Language);
   
   for( i=1 ; i<=Step ; i++ ) 
   {
      if( i==1 )                  DISPLAY("SHOW_PROGRESS_1",Language);
      else if( i==2 )             DISPLAY("SHOW_PROGRESS_2",Language);                                    
      else if( i==3 )             DISPLAY("SHOW_PROGRESS_3",Language);                        
      else if( i==4 )             DISPLAY("SHOW_PROGRESS_4",Language);                       
      else if( i==5 && Step==5 )  DISPLAY("SHOW_PROGRESS_5",Language);
      else if( i==6 )             DISPLAY("SHOW_PROGRESS_6",Language);              
    }                      
     
}

void INITIALIZE()
{
  SHOW_PROGRESS(1);
   
  COPY_FILE_HERE("MIUI_DHD_ROM\\MIUI.zip");   /* move MIUI.zip to work dic */
  
  RENAME("MIUI.zip","temp.zip");
  
  _7zUNPACK("temp.zip");
  
  DELETE_FILE("temp.zip");  
}

void YOUR_CHOICE()
{
  int flag=1;
  
  while(flag)
   {  
     UI_TOP(Language);           
     DISPLAY("ADDON_BlendUI",Language);
     Addon.BlendUI=(getchar()-'0'); 
     if ( Addon.BlendUI==1 || Addon.BlendUI==0 )  flag=0;   
   }

  flag=1;
  while(flag)
   {  
     UI_TOP(Language);           
     DISPLAY("ADDON_DSPManager",Language);
     Addon.DSPManager=(getchar()-'0'); 
     if ( Addon.DSPManager==1 || Addon.DSPManager==0 )  flag=0;   
   }     
      
  flag=1;
  while(flag)
   {  
     UI_TOP(Language);           
     DISPLAY("ADDON_SE_Media",Language);
     Addon.SE_Media=(getchar()-'0'); 
     if ( Addon.SE_Media==1 || Addon.SE_Media==0 )  flag=0;   
   }    

  flag=1;
  while(flag)
   {  
     UI_TOP(Language);           
     DISPLAY("ADDON_Tweaks",Language);
     Addon.Tweaks=(getchar()-'0'); 
     if ( Addon.Tweaks==1 || Addon.Tweaks==0 )  flag=0;   
   }       
}

void DELETE_DHD_FILES()
{
  SHOW_PROGRESS(2);    

  DELETE_DIC("META-INF");  
  DELETE_FILE("boot.img");
  DELETE_FILE("system\\etc\\bluetooth");   
  DELETE_FILE("system\\etc\\dhcpcd");
  DELETE_FILE("system\\etc\\firmware");  
  DELETE_FILE("system\\etc\\init.d");  
  DELETE_FILE("system\\etc\\wifi");   
  DELETE_FILE("system\\lib\\hw"); 
  
  DELETE_FILE("system\\app\\FM.apk"); 
  DELETE_FILE("system\\app\\Torch.apk"); 
  
  DELETE_FILE("system\\app\\FM.odex"); 
  DELETE_FILE("system\\app\\Torch.odex"); 
  DELETE_FILE("system\\app\\PackageInstaller.odex");   
  
  COPY_FILE_HERE("system\\build.prop");
               
}


void COPY_CM7_FILES()
{
  SHOW_PROGRESS(3);      
    
  if( Device.XPERIA_ARC_LT15i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\LT15i");
    }
  if( Device.XPERIA_ARC_S_LT18i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\LT15i");
     COPY_DIC_HERE("BMSPS_DATA\\LT18i");    
    }         
  if( Device.XPERIA_NEO_MT15i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\MT15i");     
    }   
  if( Device.XPERIA_NEO_V_MT11i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\MT15i");                              
     COPY_DIC_HERE("BMSPS_DATA\\MT11i");     
    }       
  if( Device.XPERIA_RAY_ST18i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\ST18i");     
    }         
  if( Device.XPERIA_PLAY_R800i )
    {
     COPY_DIC_HERE("BMSPS_DATA\\R800i");     
    }     
}


void CUSTOMIZATION()   /* will rewritte this function and add more nice stuff next time */
{
  char Ver[500];
  
  FIND_IN_FILE("ro.build.version.incremental=","build.prop",Ver);

  FILE *fout=fopen("system\\build.prop","at+");      
  fprintf(fout,"\n%s",Ver);
  fclose(fout);
  
  
  COPY_DIC_HERE("BMSPS_DATA\\Addons\\Basic");
  if(Addon.BlendUI)    COPY_DIC_HERE("BMSPS_DATA\\Addons\\BlendUI");
  if(Addon.DSPManager) COPY_DIC_HERE("BMSPS_DATA\\Addons\\DSPManager");  
  if(Addon.SE_Media)   COPY_DIC_HERE("BMSPS_DATA\\Addons\\SE_Media");  
  if(Addon.Tweaks)     COPY_DIC_HERE("BMSPS_DATA\\Addons\\Tweaks"); 

  
  _7zPACK("temp.zip","META-INF"); 
  _7zPACK("temp.zip","system"); 
  DELETE_DIC("META-INF");
  DELETE_DIC("system");
  

}


void SIGN_ROM()
{
   SHOW_PROGRESS(4);  
   SIGN("temp.zip","update.zip");  
   //RENAME("temp.zip","update.zip");
   DELETE_FILE("temp.zip");      
}

void OUTPUT_CHECK()
{
     if(FILE_CHECK("update.zip")==0)
        {
          SHOW_PROGRESS(5);  
          DISPLAY("OUTPUT_CHECK_FAILED",Language);             
          exit(1);    
        }
     else
        { 
          SHOW_PROGRESS(6);  
          DISPLAY("OUTPUT_CHECK_DONE",Language);    
        } 
         
  PAUSE();  
}


void AUTO_FLASH_FUNCTION()
{
  int flag=1;
  char Option[10];
  
  while(flag)
   {  
       UI_TOP(Language);
       DISPLAY("AUTO_FLASH",Language);   
       
      scanf("%s",Option);
      
     if ( strcmp(Option,"yes")==0 || strcmp(Option,"YES")==0 )  
       { 
          AUTO_FLASH(Language,Device); 
          flag=0; 
       }
     else if ( strcmp(Option,"no")==0 || strcmp(Option,"NO")==0 ) 
       { 
          UI_TOP(Language);
          DISPLAY("AUTO_FLASH_OFF",Language); 
          PAUSE();   
          flag=0; 
       }
   }    

}

int main()
{
  
  SETUP_WORKSPACE();      
  
  CHOSE_LANGUAGE();
  
  DESCRIPTION(); 
  
  CHOSE_DEVICE();
  
  YOUR_CHOICE();
  
  MIUI_ROM_CHECK();
  
  INITIALIZE();

  DELETE_DHD_FILES();
  
  COPY_CM7_FILES();
  
  CUSTOMIZATION();
  
  SIGN_ROM();
  
  OUTPUT_CHECK(); 
  
  CLEAN_WORKSPACE();
  
  AUTO_FLASH_FUNCTION();
  
  CLEAN_WORKSPACE();
  
  return 0;                  
           
}
