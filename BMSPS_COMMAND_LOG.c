
/*
 *  BMSPS_COMMAND_LOG.c
 *  Created on: 11-27-2011
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

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <io.h>


void WRITTE_LOG(char *Command, char *buf, int length)
{
 FILE *fin;
 fin=popen(Command,"r");
 fread(buf,sizeof(char),length,fin);
 pclose(fin);
 return;
}


int COMMAND_LOG(char *Command,char *String)   /* if find String return 1 else return 0 */
{
  char buf[500]={"0"};
  
  FILE *fwritte=fopen("mnt_log.txt","w");
 
  WRITTE_LOG(Command, buf, sizeof(buf));
  
  fprintf(fwritte,"%s",buf);  

  fclose(fwritte);
  
  if ( FIND_IN_FILE_CHECK(String,"mnt_log.txt") )  return 1;
  else return 0;
}
