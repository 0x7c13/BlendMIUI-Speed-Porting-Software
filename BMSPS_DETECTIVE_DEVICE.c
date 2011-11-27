
/*
 *  BMSPS_DETECTIVE_DEVICE.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software
 */


#include <stdio.h>
#include <conio.h>


int DETECTIVE_DEVICE()   /* if find device return 1 else return 0 */
{
  char temp[500],buf[500];
  int i=strlen("List of devices attached");
 
  FILE *fread=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("adb devices", buf, sizeof(buf));
  while( buf[i++] != '\0' )
  fprintf(fread,"%c",buf[i]);     
  fclose(fread);

  if ( FIND_IN_FILE("device","mnt_log.txt",temp) )  return 1;
  else return 0;
}

