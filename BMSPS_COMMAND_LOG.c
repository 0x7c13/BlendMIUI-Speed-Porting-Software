
/*
 *  BMSPS_COMMAND_LOG.c
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


void COMMAND_LOG(char *Command, char *buf, int length)
{
 FILE *fin;
 fin=popen(Command,"r");
 fread(buf,sizeof(char),length,fin);
 pclose(fin);
 return;
}
