#include "includes.h"

//管理员菜单 
void Menu_manager()
	{	now = time (NULL);	
		system("cls");
		printf("\n                               -----------------------   管理员系统  ----------------------                            \n");

		printf("                                                  | 1 : 采编入库.       	|\n");
	
		printf("                                                  | 2 : 清除库存.       	|\n");

		printf("                                                  | 3 : 借阅文献.         	|\n");
		
		printf("                                               	  | 4 : 归还文献.       	|\n");
				
		printf("                                                  | 5 : 查看某种文献信息.       |\n");
		
		printf("                                                  | 6 : 输出B树的状态     	|\n");
		
		printf("                                                  | 7 : 输出所有文献.   	|\n");
		
		printf("                                                  | 8 : 按作者名查阅文献 . 	|\n");
		
		printf("                                                  | 9 : 根据借阅者输出文献.     |\n");		
		
		printf("                                                  | 10 : 返回主菜单.            |\n");
		
		printf("                                                  | 11 : 保存数据到文件.            |\n");
		
		printf("                                                  | 0 : 退出系统.               |\n");
		 
		printf("                                  -------------------------------------------------------------\n");
		printf("		                      当前时间:%s  ",ctime(&now) );
		printf("\n");
		printf("                                       **************请注意保存数据！************\n" );
		
		
	}
	
//借阅者菜单 
void Menu_borrower()
{	
	now = time (NULL);	
	
	system("cls");
	
	printf("\n                                   -----------------------  借阅者系统 ---------------------- \n");                                                
	
	printf("                                                         | 1 : 借阅文献. |\n");
	
    printf("                                                         | 2 : 归还文献. |\n");
	
    printf("                                                         | 3 : 查看某种文献的信息. |\n");
	
    printf("                                                         | 4 : 输出B树的状态. |\n");

	printf("                                                         | 5 : 输出所有文献. |\n");

	printf("                                                         | 6 : 根据借阅者输出文献. |\n");
	
	printf("                                                         | 7 : 按作者名查阅文献 . 	|\n");
		
	printf("                                                         | 9 : 返回主菜单. |\n");
	
	printf("                                                         | 10 : 保存数据到文件.      |\n");
	
	printf("                                                         | 0 : 退出系统. |\n");
	
	printf("                                     -------------------------------------------------------------\n");
	printf("		                      当前时间:%s  ",ctime(&now) );
} 

//欢迎界面 		
void Welcome()
{
	now = time (NULL);	
	
	printf("\n\n\n\n\n");
	printf("		\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                 ._______________________.                    ║\n");
	printf("		\t║                 | _____________________ |                    ║\n");
	printf("		\t║                 | I                   I |                    ║\n");
	printf("		\t║                 | I    文献管理系统   I |                    ║\n");
	printf("		\t║                 | I                   I |                    ║\n");
	printf("		\t║                 | I___________________I |                    ║\n");
	printf("		\t║                 !_______________________!                    ║\n");
	printf("		\t║                     ._[__________]_.                         ║\n");
	printf("		\t║                 .___|_______________|___.                    ║\n");
	printf("		\t║                  |:::  ____            |                     ║\n");
	printf("		\t║                  |                     |                     ║\n");
	printf("		\t║                  !_____________________!                     ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║  制作者：计算机学院         20计科3班            张俊鸿      ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t╚══════════════════════════════════════════════════════════════╝\n");
	printf("		                      当前时间:%s  ",ctime(&now) );
}
//身份选择界面 
void Choose()
{	now = time (NULL);
	printf("\n\n\n");
	printf("		\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║    	  ~~~~~~~~~~~~~~请选择你的身份~~~~~~~~~~~~             ║\n");                                             
	printf("		\t║                                                              ║\n");
    printf("		\t║                        1.管理员                              ║\n");                    
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                        2.借阅者                              ║\n");        
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                        3.退出系统                            ║\n");          
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t║    	  ~~~~~~~~~~~~~~请你选择<1-3>~~~~~~~~~~~~              ║\n");     
	printf("		\t║                                                              ║\n");
	printf("		\t║                                                              ║\n");
	printf("		\t╚══════════════════════════════════════════════════════════════╝\n");
	printf("		                      当前时间:%s  ",ctime(&now) );	
}
//管理员登录验证界面 
int Login()
{
		char pass[50];	
		char password[50]="123456";          					//设置管理员密码 
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t请输入管理员密码:\n");
		printf("\n\n\n\n\n\n\n");
		printf("                                                请在此处输入:");
		scanf("%s",pass);
		if(!strcmp(pass,password))		//验证密码 
		{
		printf("\n\n\n\n\n\n\n");
		printf("===================================================登录成功！==================================================\n");
		Sleep(1500);						//登陆延时程序，产生短暂的登陆状态	
		return 1;
		}	
		else {
		printf("\n\n\n\n\n\n\n");
		printf("============================================密码错误！你没有管理员权限！========================================\n");
		Sleep(2000);						//登陆延时程序，产生短暂的登陆状态	
		system("cls");
		return -1;
	}
	return 0;
}


