
/*
 *  BMSPS_UI_PRINT.c
 *  Created on: 11-27-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  ===== BlendMIUI Speed-Porting Software V04.5 =====
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
#include <string.h>
#include <windows.h>
#include <io.h>

#include "BMSPS_LANGUAGE.h"



void HideCursor()  /* To hide Cursor */
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void DISPLAY(char *STEP,struct BMSPS_LANGUAGE Language)
{
  char p,temp[10000];   
  int i=0;
  char PATH[128]="BMSPS_LANGUAGE\\";
  
  if(Language.English) strcat(PATH,"ENG\\"); 
  if(Language.Chinese) strcat(PATH,"CHS\\");  
  
  strcat(PATH,STEP);
  
  FILE *fin=fopen(PATH,"r");
  
  while ((p=fgetc(fin))!=EOF) temp[i++]=p;
  temp[i]='\0';

  printf("%s",temp);
  fclose(fin);
}

void UI_TOP(struct BMSPS_LANGUAGE Language)  /* Always shows up on the top of the screen */
{
  system("CLS"); 
  HideCursor();  
  DISPLAY("UI_TOP",Language);  
  puts("\n");
}

