
/*
 *  BMSPS_FIND_IN_FILE.c
 *  Created on: 11-25-2011
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
#include <string.h>


int DFS_COMPARE(char *String,int Len,char *File,int i,int j)
{
  if(i==Len)
   {
    if(String[i]==File[j])  return 1;
    else return 0;
   }
  else if(String[i]!=File[j])  return 0;
  else return DFS_COMPARE(String,Len,File,i+1,j+1);
}

int FIND_IN_FILE(char *String,char *PATH,char *Ver)
{ 
  char File[500][500];
  int  Lines=0 , i=0 , j=0 ,flag=0 ;
  int Length=strlen(String);
   
  FILE *fread=fopen(PATH,"r");
  
  while(fgets(File[Lines++],500,fread));
  
  for( i=0 ; i<Lines ; i++ )
  { 
    j=0;
    while( File[i][j]!='\0' )
     if(DFS_COMPARE(String,Length-1,File[i],0,j)) 
       { flag=1; break; }
     else j++;
    if(flag) break; 
  }
  
  strcpy(Ver,File[i]);
  fclose(fread);
  
  if(flag) return 1;
  else     return 0;
}

int FIND_IN_FILE_CHECK(char *String,char *PATH)
{ 
  char File[500][500];
  int  Lines=0 , i=0 , j=0 ,flag=0 ;
  int Length=strlen(String);
   
  FILE *fread=fopen(PATH,"r");
  
  while(fgets(File[Lines++],500,fread));
  
  for( i=0 ; i<Lines ; i++ )
  { 
    j=0;
    while( File[i][j]!='\0' )
     if(DFS_COMPARE(String,Length-1,File[i],0,j)) 
       { flag=1; break; }
     else j++;
    if(flag) break; 
  }

  fclose(fread);
  
  if(flag) return 1;
  else     return 0;
}
