
/*
 *  BMSPS_REBOOT_INTO_FASTBOOT_MODE.c
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
#include <windows.h>
#include <io.h>


int REBOOT_INTO_FASTBOOT_MODE()   /* if device is under fastboot mode return 1 else return 0 */
{
  char buf[500];
 
  FILE *fout=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("fastboot devices", buf, sizeof(buf));
  fprintf(fout,"%s",buf);     
  
  fclose(fout);
   
  if ( FIND_IN_FILE_CHECK("fastboot","mnt_log.txt") )  return 1;
  else return 0;
} 


