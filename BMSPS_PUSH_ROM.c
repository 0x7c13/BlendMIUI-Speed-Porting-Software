
/*
 *  BMSPS_PUSH_ROM.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software
 */


#include <stdio.h>
#include <conio.h>


int PUSH_ROM()   /* if the rom has been pushed return 1 else return 0 */
{
  char temp[500],buf[500];
  int i=strlen("List of devices attached");
 
  FILE *fread=fopen("mnt_log.txt","w");
 
  COMMAND_LOG("adb push update.zip /mnt/sdcard", buf, sizeof(buf));
  while( buf[i++] != '\0' )
  fprintf(fread,"%c",buf[i]);     
  fclose(fread);

  if ( FIND_IN_FILE("KB/s","mnt_log.txt",temp) )  return 1;
  else return 0;
}

