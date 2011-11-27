
/*
 *  BMSPS_DETECTIVE_USB_STORAGE_MODE.c
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



int DETECTIVE_USB_STORAGE_MODE()   /* if open return 1 else return 0 */
{
  char buf[500];
 
  FILE *fout=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("adb shell ls -l /mnt", buf, sizeof(buf));
  fprintf(fout,"%s",buf);     
  
  fclose(fout);
   
  if ( FIND_IN_FILE_CHECK("sdcard_r","mnt_log.txt")==0 )  return 1;
  else return 0;
}

