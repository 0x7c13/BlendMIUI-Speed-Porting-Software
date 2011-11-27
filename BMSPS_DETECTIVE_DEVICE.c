
/*
 *  BMSPS_DETECTIVE_DEVICE.c
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


int DETECTIVE_DEVICE()   /* if find device return 1 else return 0 */
{
  char buf[500];
  int i=strlen("List of devices attached");
 
  FILE *fread=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("adb devices", buf, sizeof(buf));
  while( buf[i++] != '\0' )
  fprintf(fread,"%c",buf[i]);     
  fclose(fread);

  if ( FIND_IN_FILE_CHECK("device","mnt_log.txt") )  return 1;
  else return 0;
}

