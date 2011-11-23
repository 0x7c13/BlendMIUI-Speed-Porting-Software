/* Written By JasonStein E-mail:JasonStein@live.cn */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>

char BMSPS_VERSION[]="V02";      //the version of BlendMIUI Speed-Porting Software
char BMSPS_DATE[]="11-23-2011";  //Building date
int Language;  // ENG:1  CHS:2
int Device;    // ARC:1  ARC S:2  NEO:3

int file_exists(char *filename);

void HideCursor()  // To hide Cursor
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


int file_exists(char *filename)
{
  return (access(filename, 0) == 0);
}


int Rom_Check() // Ensure MIUI.zip is under MIUI_DHD_ROM directory
{
 if (file_exists("MIUI_DHD_ROM\\MIUI.zip")) return 1;
  else return 0;
}

int Out_Check()  // Ensure update.zip has been created successfully
{
 if (file_exists("update.zip")) return 1;
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
         "............................Version:%s Date:%s........................\n",
         BMSPS_VERSION,BMSPS_DATE);  
  }
  else if(Language==2){
  printf("=================== XPERIA ARC & NEO BlendMIUI 快速移植软件 ===================\n"
         ".            作者:JasonStein  源代码已上传至:github.com/JasonStein            .\n"
         ".                 特别感谢: Bheremans,EAMARS,FXP TEAM,DooMLoRd                .\n"
         ".........................当前版本:%s 编译日期:%s......................\n",
         BMSPS_VERSION,BMSPS_DATE); 
  }       
  
}

void Description()
{
  UI_TOP();   
  
  if(Language==1){
  printf("\nWhat is BlendMIUI Speed-Porting Software For XPERIA ARC & NEO ?\n"
         "This is a short program trying to help you guys to build your own BlendMIUI rom for Xperia Arc and Neo in just few minutes.\n"
         "\nWhat should I do now?\n"
         "1.Make sure You have installed Java SE JRE which can be downloaded from Oracle.com/java\n"
         "2.Please go to MIUI.com or MIUI.us to download the lates MIUI rom for Desire HD\n"
         "3.Rename the rom you just downloaded as MIUI.zip then put it into \\MIUI_DHD_ROM directory\n"
         "\n\nPress Any Key to continue.");  
  }
  else if(Language==2){
  printf("\n什么是 XPERIA ARC & NEO BlendMIUI 快速移植软件 ?\n"
         "这是我写的一个小软件，帮助大家在很短的时间内给XPERIA ARC和NEO移植MIUI并生成刷机包.\n"
         "\n现在我需要做什么?\n"
         "1.确保已经安装JAVA环境，可以搜索JAVA SE JRE后下载安装，也可以去官网下载:Oracle.com/java\n"
         "2.去 miui.com 或 miui.us (建议去这里)下载Desire HD最新版的MIUI rom\n"
         "3.把下载好的 MIUI Rom 改名为 MIUI.zip 并放入本软件 \\MIUI_DHD_ROM 目录下\n"
         "\n\n如果你已经阅读完以上信息，请随便按一个键继续");     
  }
  getch();
}

void Chose_Device()
{
  int flag=1;
  
  while(flag){  
                UI_TOP(); 
                
                   if(Language==1){
                                    printf("\nChose your Device:\n\n"
                                           "1.Sony Ericsson Xperia Arc LT15i\n"
                                           "2.Sony Ericsson Xperia Arc S LT18i\n"
                                           "3.Sony Ericsson Xperia Neo MT15i\n"
                                           "\nInput the Number then Press Enter to confirm:");  
                                  }
              else if(Language==2){
                                    printf("\n请选择你的机型:\n\n"
                                           "1.Sony Ericsson Xperia Arc LT15i\n"
                                           "2.Sony Ericsson Xperia Arc S LT18i\n"
                                           "3.Sony Ericsson Xperia Neo MT15i\n"
                                           "\n输入序号并按回车键确认:");  
                                  }
     Device=(getchar()-'0');
     if ( Device==1 || Device==2 || Device==3)  flag=0;   
  }
}

void Check()
{
     while(Rom_Check()==0)
     {
       UI_TOP();    
                    
             if(Language==1){
                              printf("\nMake sure you have put MIUI.zip into \\MIUI_DHD_ROM directory!!!\n"  
                                     "\nIf you have put it into MIUI_DHD_ROM directory just press any key to continue\n"); 
                            }
        else if(Language==2){
                              printf("\n请确保你已经把 MIUI.zip 放入本软件 \\MIUI_DHD_ROM 目录下!!!\n"  
                                     "\n如果你已经正确放入，请按任意键继续\n"); 
                            }                     
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
   Show_Progress(5);          
}

void Done()
{
    
     if(Out_Check()==0)
     {
        Show_Progress(5);  
             if(Language==1){                               
                              printf("\nERROR:update.zip hasn't been created under main menu!!!\n"  
                                     "\nWhat should I do now?:\n"
                                     "1.Download JAVA-SE-JRE from oracle.com/Java.\n"
                                     "2.Restart this software to do it again.\n"
                                     "\n\nPress any key to exit."); 
                            }
        else if(Language==2){   
                              printf("\n警告: update.zip 并没有成功生成于主目录下!!!\n"  
                                     "\n接下来你需要: \n"
                                     "1.安装Java-SE-JRE\n"
                                     "2.重新启动本程序.\n"
                                     "\n\n按任意键即可退出本程序"); 
                            }       
     
     }
     else{ 
             Show_Progress(6);     
              
             if(Language==1){
                              printf("\nupdate.zip has been created successfully under main directory of this software!!!\n"  
                                     "\nNext:\n"
                                     "1.Put update.zip into SD-card\n"
                                     "2.Flash BlendMIUI kernel which is under BlendMIUI-kernel\\ directory or you can flash DooMKernel for MIUI.\n"
                                     "3.Use CWM-recovery to flash update.zip rom."
                                     "\n\nPress any key to exit."); 
                            }
        else if(Language==2){
                              printf("\n注意: update.zip 刷机包已经成功生成于本软件的主目录下!!!\n"  
                                     "\n接下来你需要: \n"
                                     "1.把 update.zip 拷贝进SD卡\n"
                                     "2.使用 fastboot 刷入我放在本软件 BlendMIUI-kernel\\ 目录下的 boot.img 内核.\n"
                                     "3.启动手机连续按返回键或音量降低键进入CWM-Recovery刷入update.zip."
                                     "\n\n按任意键即可退出本程序"); 
                            }   
        } 
  getch();
}


int main()
{
    
  Chose_Language();
  
  Description(); 
  
  Chose_Device();
  
  Check();
  
  Initialize();

  Delete_Files();
  
  Copy_Files();
  
  Sign_Rom();
  
  Done();
  
  return 0;                  
           
}
