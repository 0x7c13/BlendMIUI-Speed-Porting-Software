
/*
 *  BMSPS_DETECTIVE_USB_STORAGE_MODE.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software
 */


#include <stdio.h>
#include <conio.h>



int DETECTIVE_USB_STORAGE_MODE()   /* if open return 1 else return 0 */
{
  char temp[500],buf[500];
 
  FILE *fout=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("adb shell ls -l /mnt", buf, sizeof(buf));
  fprintf(fout,"%s",buf);     
  
  fclose(fout);
   
  if ( FIND_IN_FILE("sdcard_r","mnt_log.txt",temp)==0 )  return 1;
  else return 0;
}

