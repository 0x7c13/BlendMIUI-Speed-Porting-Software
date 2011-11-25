
/*
 *  BMSPS_launcher.c
 *  Created on: 11-25-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software V03.1
 */


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>

/* My files */
#include "BMSPS_LANGUAGE.h"
#include "BMSPS_DEVICE.h"
#include "BMSPS_ADDON.h"

#include "BMSPS_BASIC_FUNCTIONS.c"
#include "BMSPS_FIND_IN_BUILD.c"
/* My files */


struct BMSPS_LANGUAGE Language;
struct BMSPS_DEVICE Device;
struct BMSPS_ADDON Addon;



void CLEAN_WORKSPACE()
{
  /* Clean */   
  DELETE_DIC("META-INF");  
  DELETE_DIC("system");
  DELETE_FILE("boot.img");
  DELETE_FILE("temp.zip");
  DELETE_FILE("build.prop");
  DELETE_FILE("build_MIUI.prop");  
  DELETE_FILE("BMSPS_DATA\\Addon\\Build\\system\\build.prop");  
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
  
  Addon.BlendUI=0;
  Addon.DSPManager=0;
  Addon.SE_Media=0;
  Addon.Tweaks=0;
  /* set defult value */    
  
  CLEAN_WORKSPACE();        
}



void DISPLAY(char *STEP)
{
  char p;   
  
  char PATH[128]="BMSPS_LANGUAGE\\";
  
  if(Language.English) strcat(PATH,"ENG\\"); 
  if(Language.Chinese) strcat(PATH,"CHS\\");  
  
  strcat(PATH,STEP);
  
  FILE *fin=fopen(PATH,"r");
  
  while ((p=fgetc(fin))!=EOF) printf("%c",p);

  fclose(fin);
}



void UI_TOP()  /* Always shows up on the top of the screen */
{
  system("CLS"); 
  HideCursor();    
  DISPLAY("UI_TOP");  
  puts("\n");
}



void CHOSE_LANGUAGE()
{
  int flag=1,Option;
   
  while(flag)
  {   
     system("CLS"); 
     HideCursor();      
     
     DISPLAY("CHOSE_LANGUAGE");   
  
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
  UI_TOP();   
  
  DISPLAY("DESCRIPTION");
  
  PAUSE();
}

void CHOSE_DEVICE()
{
  int flag=1,Option;
  
  while(flag)
   {  
     UI_TOP(); 
                
     DISPLAY("CHOSE_DEVICE"); 
     
     Option=(getchar()-'0');
     
     if ( Option==1 || Option==2 || Option==3 )  flag=0;   
   }
   
  switch(Option)
   {
      case 1: { Device.XPERIA_ARC_LT15i=1;   break;}
      case 2: { Device.XPERIA_ARC_S_LT18i=1; break;}
      case 3: { Device.XPERIA_NEO_MT15i=1;   break;}      
   }
}

void MIUI_ROM_CHECK()
{
     while(FILE_CHECK("MIUI_DHD_ROM\\MIUI.zip")==0)
     {
       UI_TOP();    
       
       DISPLAY("MIUI_ROM_CHECK");             
                   
       PAUSE();                              
     }
}

void SHOW_PROGRESS(Step)
{
   int i;
   
   UI_TOP();
   
   for( i=1 ; i<=Step ; i++ ) 
   {
      if( i==1 )                  DISPLAY("SHOW_PROGRESS_1");
      else if( i==2 )             DISPLAY("SHOW_PROGRESS_2");                                    
      else if( i==3 )             DISPLAY("SHOW_PROGRESS_3");                        
      else if( i==4 )             DISPLAY("SHOW_PROGRESS_4");                       
      else if( i==5 && Step==5 )  DISPLAY("SHOW_PROGRESS_5");
      else if( i==6 )             DISPLAY("SHOW_PROGRESS_6");              
    }                      
     
}

void INITIALIZE()
{
  SHOW_PROGRESS(1);
   
  COPY_FILE("MIUI_DHD_ROM\\MIUI.zip","temp.zip");   /* move MIUI.zip to work dic */
  
  _7zUNPACK("temp.zip");

  DELETE_FILE("temp.zip");
}

void YOUR_CHOICE()
{
  int flag=1;
  
  while(flag)
   {  
     UI_TOP();           
     DISPLAY("ADDON_BlendUI");
     Addon.BlendUI=(getchar()-'0'); 
     if ( Addon.BlendUI==1 || Addon.BlendUI==0 )  flag=0;   
   }

  flag=1;
  while(flag)
   {  
     UI_TOP();           
     DISPLAY("ADDON_DSPManager");
     Addon.DSPManager=(getchar()-'0'); 
     if ( Addon.DSPManager==1 || Addon.DSPManager==0 )  flag=0;   
   }     
      
  flag=1;
  while(flag)
   {  
     UI_TOP();           
     DISPLAY("ADDON_SE_Media");
     Addon.SE_Media=(getchar()-'0'); 
     if ( Addon.SE_Media==1 || Addon.SE_Media==0 )  flag=0;   
   }    

  flag=1;
  while(flag)
   {  
     UI_TOP();           
     DISPLAY("ADDON_Tweaks");
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
  
  COPY_FILE("system\\build.prop","build_MIUI.prop");
  
  _7zPACK("temp.zip","system"); 
  
  DELETE_DIC("system");              
}


void COPY_CM7_FILES()
{
  SHOW_PROGRESS(3);      
    
  if( Device.XPERIA_ARC_LT15i )
    {
     _7zPACK("temp.zip",".\\BMSPS_DATA\\LT15i\\*");
     COPY_FILE("BMSPS_DATA\\LT15i\\system\\build.prop","build.prop");
    }
  if( Device.XPERIA_ARC_S_LT18i )
    {
     _7zPACK("temp.zip",".\\BMSPS_DATA\\LT15i\\*");
     _7zPACK("temp.zip",".\\BMSPS_DATA\\LT18i\\*"); 
     COPY_FILE("BMSPS_DATA\\LT18i\\system\\build.prop","build.prop");       
    }         
  if( Device.XPERIA_NEO_MT15i )
    {
     _7zPACK("temp.zip",".\\BMSPS_DATA\\MT15i\\*");     
     COPY_FILE("BMSPS_DATA\\MT15i\\system\\build.prop","build.prop");       
    }       

}


void CUSTOMIZATION()   /* will rewritte this function and add more nice stuff next time */
{
  char Ver[500];
  
  FIND_IN_BUILD("ro.build.version.incremental=","build_MIUI.prop",Ver);

  FILE *fout=fopen("build.prop","at+");      
  fprintf(fout,"\n%s",Ver);
  fclose(fout);
  
  COPY_FILE("build.prop","BMSPS_DATA\\Addon\\Build\\system\\build.prop");  
  _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\Build\\*");
  
  _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\Basic\\*");
  if(Addon.BlendUI)    _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\BlendUI\\*");
  if(Addon.DSPManager) _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\DSPManager\\*");  
  if(Addon.SE_Media)   _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\SE_Media\\*");  
  if(Addon.Tweaks)     _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\Tweaks\\*"); 

}


void SIGN_ROM()
{
   SHOW_PROGRESS(4);  
   system("java -jar signapk.jar testkey.x509.pem testkey.pk8 temp.zip update.zip");  
   DELETE_FILE("temp.zip");              
}

void OUTPUT_CHECK()
{
     if(FILE_CHECK("update.zip")==0)
        {
          SHOW_PROGRESS(5);  
          DISPLAY("OUTPUT_CHECK_FAILED");       
        }
     else
        { 
          SHOW_PROGRESS(6);  
          DISPLAY("OUTPUT_CHECK_DONE");    
        }   
  PAUSE();
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
  
  return 0;                  
           
}
