
/*
 *  BMSPS_BASIC_FUNCTIONS.c
 *  Created on: 11-25-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software V03.1
 */


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>


void HideCursor()  /* To hide Cursor */
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void PAUSE()
{
 getch();     
}

int FILE_CHECK(char *PATH) 
{   
 if ((access(PATH, 0) == 0)) return 1;
  else return 0;
}

void DELETE_FILE(char *PATH)   /* Delete single file */
{
  char DEL[128]="del /F /Q ";
  strcat(DEL,PATH);
  if(FILE_CHECK(PATH)) system(DEL);
}

void DELETE_DIC(char *PATH)    /* Delete folder */
{
  char DEL[128]="RD /S /Q ";
  strcat(DEL,PATH);
  if(FILE_CHECK(PATH)) system(DEL);    
}

void COPY_FILE(char *A,char *B)   /* Copy file from A to B */
{
  char Copy[128]="copy ";
  strcat(Copy,A);  
  strcat(Copy," ");   
  strcat(Copy,B); 
  
  system(Copy);
}

void _7zPACK(char *A,char *B)  /* Use 7z to Pack B folder into A file */
{
  char Pack[128]="7z a ";     
  strcat(Pack,A);  
  strcat(Pack," ");   
  strcat(Pack,B);   
    
  system(Pack); 
}


void _7zUNPACK(char *PATH)    /* Use 7z to upack */
{
  char Unpack[128]="7z x ";      
  strcat(Unpack,PATH);  
  system(Unpack);       
}

