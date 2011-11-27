
/*
 *  BMSPS_COMMAND_LOG.c
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


void COMMAND_LOG(char *Command, char *buf, int length)
{
 FILE *fin;
 fin=popen(Command,"r");
 fread(buf,sizeof(char),length,fin);
 pclose(fin);
 return;
}
