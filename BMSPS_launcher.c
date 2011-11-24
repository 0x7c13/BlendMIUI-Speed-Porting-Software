/* Written By JasonStein E-mail:JasonStein@live.cn */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>

char BMSPS_VERSION[]="V02.1";      //the version of BlendMIUI Speed-Porting Software
char BMSPS_DATE[]="11-24-2011";  //Building date
int Language;  // ENG:1  CHS:2
int Device;    // ARC:1  ARC S:2  NEO:3

int file_exists(char *filename);


void HideCursor()  // To hide Cursor
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


int FILE_CHECK(char *PATH) 
{   
 if ((access(PATH, 0) == 0)) return 1;
  else return 0;
}


void Chose_Language()
{
  int flag=1;
   
  while(flag)
  {   
     system("CLS"); 
     HideCursor();      
     printf("Chose Language | 选择语言 :\n\n");
     printf("1.English | 英语\n2.Chinese | 简体中文\n");                  
     printf("\nInput the Number then Press Enter to confirm | 输入序号后回车确认:");    
  
     Language=(getchar()-'0');
     if ( Language==1 || Language==2 )  flag=0;
  } 
    
}

void UI_TOP()  // Always shows up on the top of the screen
{
  system("CLS"); 
  HideCursor();    
  if(Language==1){
  printf("============ BlendMIUI Speed-Porting Software For XPERIA ARC & NEO ============\n"
         "|         Written By JasonStein. Source Code @ github.com/JasonStein          |\n"
         "|                Credit: Bheremans,EAMARS,FXP TEAM,DooMLoRd                   |\n"
         "...........................Version:%s Date:%s.......................\n",
         BMSPS_VERSION,BMSPS_DATE);  
  }
  else if(Language==2){
  printf("=================== XPERIA ARC & NEO BlendMIUI 快速移植软件 ===================\n"
         ".            作者:JasonStein  源代码已上传至:github.com/JasonStein            .\n"
         ".                 特别感谢: Bheremans,EAMARS,FXP TEAM,DooMLoRd                .\n"
         "........................当前版本:%s 编译日期:%s.....................\n",
         BMSPS_VERSION,BMSPS_DATE); 
  }       
  
}

void Display(char *STEP)
{
  char p;   
  
  char PATH[128]="BMSPS_LANGUAGE\\";
  if(Language==1) strcat(PATH,"ENG\\"); 
  else if(Language==2) strcat(PATH,"CHS\\");  
  strcat(PATH,STEP);
  
  FILE *fin=fopen(PATH,"r");
  
  while ((p=fgetc(fin))!=EOF) printf("%c",p);

  fclose(fin);
}

void Description()
{
  UI_TOP();   
  
  Display("Description");
  
  getch();
}

void Chose_Device()
{
  int flag=1;
  
  while(flag)
   {  
     UI_TOP(); 
                
     Display("Chose_Device"); 
     
     Device=(getchar()-'0');
     
     if ( Device==1 || Device==2 || Device==3)  flag=0;   
   }
}

void MIUI_ROM_Check()
{
     while(FILE_CHECK("MIUI_DHD_ROM\\MIUI.zip")==0)
     {
       UI_TOP();    
       
       Display("MIUI_ROM_Check");             
                   
       getch();                              
     }
}

void Show_Progress(Step)
{
   int i;
   
   UI_TOP();
   
   if(Language==1){   
       for(i=1;i<=Step;i++)
        {
         if( i==1 )  printf("\nProgress:\n\n1.Initializing... "); 
         if( i==2 )  printf("Done!\n2.Deleting Files... ");                                       
         if( i==3 )  printf("Done!\n3.Copying Files... ");                          
         if( i==4 )  printf("Done!\n4.Signing... ");                         
         if( i==5 && Step==5 )  printf("Failed!\n");  
         if( i==6 )  printf("Done!\n");              
        }                      
   }
  else if(Language==2){   
       for(i=1;i<=Step;i++)
        {
         if( i==1 )  printf("\n当前进度:\n\n1.初始化中... ");                               
         if( i==2 )  printf("完成!\n2.删除文件中... ");                          
         if( i==3 )  printf("完成!\n3.复制文件中... ");   
         if( i==4 )  printf("完成!\n4.正在打包签名... ");                                
         if( i==5 && Step==5 )  printf("失败!\n");     
         if( i==6 )  printf("完成!\n");                               
        }              
   } 
     
}

void Initialize()
{
  Show_Progress(1);
   
  system("copy MIUI_DHD_ROM\\MIUI.zip MIUI.zip");   
  system("7z x MIUI.zip");
  system("del MIUI.zip");
}

void Delete_Files()
{
  Show_Progress(2);    
  
  system("del boot.img");    
  system("RD /S /Q META-INF");
  system("del /F /S /Q system\\etc\\bluetooth");   
  system("del /F /S /Q system\\etc\\dhcpcd");
  system("del /F /S /Q system\\etc\\firmware");  
  system("del /F /S /Q system\\etc\\init.d");  
  system("del /F /S /Q system\\etc\\wifi");   
  system("del /F /S /Q system\\lib\\hw"); 
  
  system("del /F /S /Q system\\app\\FM.apk"); 
  system("del /F /S /Q system\\app\\Torch.apk"); 
  system("del /F /S /Q system\\build.prop"); 
  
  if(FILE_CHECK("system\\app\\FM.odex"))
    system("del /F /S /Q system\\app\\FM.odex"); 
  if(FILE_CHECK("system\\app\\Torch.odex"))
    system("del /F /S /Q system\\app\\Torch.odex"); 
  if(FILE_CHECK("system\\app\\PackageInstaller.odex"))
    system("del /F /S /Q system\\app\\PackageInstaller.odex");   
      
  system("7z a temp.zip system"); 
 
  system("RD /S /Q system");               
}


void Copy_Files()
{
  Show_Progress(3);      

  system("7z x DATA.bms"); 
  
  if( Device==1 || Device==2 )
     system("7z a temp.zip .\\DATA\\LT15i\\*");
  if( Device==2 )
     system("7z a temp.zip .\\DATA\\LT18i\\*");             
  if( Device==3 )
     system("7z a temp.zip .\\DATA\\MT15i\\*");     
  
  system("7z a temp.zip .\\DATA\\Addon\\*");  //Addon    
  
  system("RD /S /Q DATA");      
       
}

void Sign_Rom()
{
   Show_Progress(4);  
   system("java -jar signapk.jar testkey.x509.pem testkey.pk8 temp.zip update.zip");  
   system("del temp.zip");              
}

void OUTPUT_Check()
{
    
     if(FILE_CHECK("update.zip")==0)
        {
          Show_Progress(5);  
          Display("OUTPUT_Check_Failed");       
        }
     else
        { 
            Show_Progress(6);     
            Display("OUTPUT_Check_Done");     
        } 
  system("RD /S /Q BMSPS_LANGUAGE");       
  getch();
}


int main()
{
  system("7z x BMSPS_LANGUAGE.bms");     
  
  Chose_Language();
  
  Description(); 
  
  Chose_Device();
  
  MIUI_ROM_Check();
  
  Initialize();

  Delete_Files();
  
  Copy_Files();
  
  Sign_Rom();
  
  OUTPUT_Check();
  
  return 0;                  
           
}
