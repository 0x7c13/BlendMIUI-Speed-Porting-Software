
/*
 *  BMSPS_launcher.c
 *  Created on: 11-24-2011
 *  Author: JasonStein
 *  E-mail:JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software V02.5
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
#include "BMSPS_FIND_IN_BUILD.c"
/* My files */

struct BMSPS_LANGUAGE Language;
struct BMSPS_DEVICE Device;

void HideCursor()  /* To hide Cursor */
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


int FILE_CHECK(char *PATH) 
{   
 if ((access(PATH, 0) == 0)) return 1;
  else return 0;
}

void DELETE_FILE(char *PATH)   /* Delete single file */
{
  char DEL[128]="del /F /Q ";
  strcat(DEL,PATH);
  if(FILE_CHECK(PATH)) system(DEL);
}

void DELETE_DIC(char *PATH)    /* Delete folder */
{
  char DEL[128]="RD /S /Q ";
  strcat(DEL,PATH);
  if(FILE_CHECK(PATH)) system(DEL);    
}

void COPY_FILE(char *A,char *B)   /* Copy file from A to B */
{
  char Copy[128]="copy ";
  strcat(Copy,A);  
  strcat(Copy," ");   
  strcat(Copy,B); 
  
  system(Copy);
}

void _7zPACK(char *A,char *B)  /* Use 7z to Pack B folder into A file */
{
  char Pack[128]="7z a ";     
  strcat(Pack,A);  
  strcat(Pack," ");   
  strcat(Pack,B);   
    
  system(Pack); 
}


void _7zUNPACK(char *PATH)    /* Use 7z to upack */
{
  char Unpack[128]="7z x ";      
  strcat(Unpack,PATH);  
  system(Unpack);       
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

void UI_TOP()  /* Always shows up on the top of the screen */
{
  system("CLS"); 
  HideCursor();    
  DISPLAY("UI_TOP");  
}


void DESCRIPTION()
{
  UI_TOP();   
  
  DISPLAY("DESCRIPTION");
  
  getch();
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
                   
       getch();                              
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
   
  COPY_FILE("MIUI_DHD_ROM\\MIUI.zip","temp.zip");   
  
  _7zUNPACK("temp.zip");

  DELETE_FILE("temp.zip");
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
      COPY_FILE("copy BMSPS_DATA\\LT18i\\system\\build.prop","build.prop");       
    }         
  if( Device.XPERIA_NEO_MT15i )
    {
     _7zPACK("temp.zip",".\\BMSPS_DATA\\MT15i\\*");     
      COPY_FILE("copy BMSPS_DATA\\MT15i\\system\\build.prop","build.prop");       
    }       

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
  getch();
}

void CLEAN_WORKSPACE()
{
  /* Clean */   
  DELETE_DIC("META-INF");  
  DELETE_DIC("system");
  DELETE_FILE("boot.img");
  DELETE_FILE("temp.zip");
  DELETE_FILE("build.prop");
  DELETE_FILE("build_MIUI.prop");  
  DELETE_FILE("BMSPS_DATA\\Addon\\system\\build.prop");  
  /* Clean */       
}


void SETUP_WORKSPACE()
{
  Language.English=0;
  Language.Chinese=0;
  
  Device.XPERIA_ARC_LT15i=0;
  Device.XPERIA_ARC_S_LT18i=0;
  Device.XPERIA_NEO_MT15i=0;
  
  CLEAN_WORKSPACE();        
}


void CUSTOMIZATION()   /* will rewritte this function and add more nice stuff next time */
{

  char Ver[500];
  
  FIND_IN_BUILD("ro.build.version.incremental=","build_MIUI.prop",Ver);

  FILE *fout;
  fout=fopen("build.prop","at+");      
  fprintf(fout,"\n%s\n",Ver);
  fclose(fout);
  
  COPY_FILE("build.prop","BMSPS_DATA\\Addon\\system\\build.prop");  
  
  _7zPACK("temp.zip",".\\BMSPS_DATA\\Addon\\*");  

}


int main()
{

    
  SETUP_WORKSPACE();      
  
  CHOSE_LANGUAGE();
  
  DESCRIPTION(); 
  
  CHOSE_DEVICE();
  
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
