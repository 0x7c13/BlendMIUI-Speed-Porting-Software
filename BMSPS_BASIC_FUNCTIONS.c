
/*
 *  BMSPS_BASIC_FUNCTIONS.c
 *  Created on: 11-25-2011
 *  Author: JasonStein
 *  E-mail: JasonStein@live.cn
 *
 *  BlendMIUI Speed-Porting Software
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
  strcat(DEL," > temp_log.txt");  
  if(FILE_CHECK(PATH)) system(DEL);
}

void DELETE_DIC(char *PATH)    /* Delete folder */
{
  char DEL[128]="RD /S /Q ";
  strcat(DEL,PATH);
  strcat(DEL," > temp_log.txt");    
  if(FILE_CHECK(PATH)) system(DEL);    
}

void COPY_FILE(char *A,char *B)   /* Copy file from A to B */
{
  char Copy[128]="xcopy ";
  strcat(Copy,A);  
  strcat(Copy," ");   
  strcat(Copy,B); 
  strcat(Copy," /Q /Y");  
  strcat(Copy," > temp_log.txt");      
  system(Copy);
}

void COPY_FILE_HERE(char *PATH)   /* Copy file from PATH to main Dic (workspace)  */
{
  char Copy[128]="xcopy ";
  strcat(Copy,PATH);  
  strcat(Copy," /Q /Y");  
  strcat(Copy," > temp_log.txt");    
  system(Copy);
}

void COPY_DIC_HERE(char *PATH)   /* Copy Dic from PATH to main Dic (workspace) */
{
  char Copy[128]="xcopy ";
  strcat(Copy,PATH);  
  strcat(Copy," /E /Q /Y");  
  strcat(Copy," > temp_log.txt");     
  system(Copy);
}

void RENAME(char *A,char *B)  
{
  char Rename[128]="ren ";
  strcat(Rename,A);  
  strcat(Rename," ");   
  strcat(Rename,B); 
  strcat(Rename," > temp_log.txt");       
  
  system(Rename);    
     
}

void _7zPACK(char *A,char *B)  /* Use 7z to Pack B folder into A file */
{
  char Pack[128]="7z a ";     
  strcat(Pack,A);  
  strcat(Pack," ");   
  strcat(Pack,B);   
  strcat(Pack," > temp_log.txt");  
      
  system(Pack); 
}


void _7zUNPACK(char *PATH)    /* Use 7z to upack */
{
  char Unpack[128]="7z x ";      
  strcat(Unpack,PATH); 
  strcat(Unpack," > temp_log.txt");  
     
  system(Unpack);       
}

void SIGN(char *A,char *B)
{
  char Sign[123]="java -jar signapk.jar testkey.x509.pem testkey.pk8 ";     
  strcat(Sign,A);
  strcat(Sign," ");
  strcat(Sign,B);
  strcat(Sign," > temp_log.txt");
  
  system(Sign);   
}
