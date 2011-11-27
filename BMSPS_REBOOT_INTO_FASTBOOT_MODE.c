
/*
 *  BMSPS_REBOOT_INTO_FASTBOOT_MODE.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software
 */


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <io.h>


int REBOOT_INTO_FASTBOOT_MODE()   /* if device is under fastboot mode return 1 else return 0 */
{
  char temp[500],buf[500];
 
  FILE *fout=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("fastboot devices", buf, sizeof(buf));
  fprintf(fout,"%s",buf);     
  
  fclose(fout);
   
  if ( FIND_IN_FILE("fastboot","mnt_log.txt",temp) )  return 1;
  else return 0;
} 


