#include "includes.h"

//����Ա�˵� 
void Menu_manager()
	{	now = time (NULL);	
		system("cls");
		printf("\n                               -----------------------   ����Աϵͳ  ----------------------                            \n");

		printf("                                                  | 1 : �ɱ����.       	|\n");
	
		printf("                                                  | 2 : ������.       	|\n");

		printf("                                                  | 3 : ��������.         	|\n");
		
		printf("                                               	  | 4 : �黹����.       	|\n");
				
		printf("                                                  | 5 : �鿴ĳ��������Ϣ.       |\n");
		
		printf("                                                  | 6 : ���B����״̬     	|\n");
		
		printf("                                                  | 7 : �����������.   	|\n");
		
		printf("                                                  | 8 : ���������������� . 	|\n");
		
		printf("                                                  | 9 : ���ݽ������������.     |\n");		
		
		printf("                                                  | 10 : �������˵�.            |\n");
		
		printf("                                                  | 11 : �������ݵ��ļ�.            |\n");
		
		printf("                                                  | 0 : �˳�ϵͳ.               |\n");
		 
		printf("                                  -------------------------------------------------------------\n");
		printf("		                      ��ǰʱ��:%s  ",ctime(&now) );
		printf("\n");
		printf("                                       **************��ע�Ᵽ�����ݣ�************\n" );
		
		
	}
	
//�����߲˵� 
void Menu_borrower()
{	
	now = time (NULL);	
	
	system("cls");
	
	printf("\n                                   -----------------------  ������ϵͳ ---------------------- \n");                                                
	
	printf("                                                         | 1 : ��������. |\n");
	
    printf("                                                         | 2 : �黹����. |\n");
	
    printf("                                                         | 3 : �鿴ĳ�����׵���Ϣ. |\n");
	
    printf("                                                         | 4 : ���B����״̬. |\n");

	printf("                                                         | 5 : �����������. |\n");

	printf("                                                         | 6 : ���ݽ������������. |\n");
	
	printf("                                                         | 7 : ���������������� . 	|\n");
		
	printf("                                                         | 9 : �������˵�. |\n");
	
	printf("                                                         | 10 : �������ݵ��ļ�.      |\n");
	
	printf("                                                         | 0 : �˳�ϵͳ. |\n");
	
	printf("                                     -------------------------------------------------------------\n");
	printf("		                      ��ǰʱ��:%s  ",ctime(&now) );
} 

//��ӭ���� 		
void Welcome()
{
	now = time (NULL);	
	
	printf("\n\n\n\n\n");
	printf("		\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                 ._______________________.                    �U\n");
	printf("		\t�U                 | _____________________ |                    �U\n");
	printf("		\t�U                 | I                   I |                    �U\n");
	printf("		\t�U                 | I    ���׹���ϵͳ   I |                    �U\n");
	printf("		\t�U                 | I                   I |                    �U\n");
	printf("		\t�U                 | I___________________I |                    �U\n");
	printf("		\t�U                 !_______________________!                    �U\n");
	printf("		\t�U                     ._[__________]_.                         �U\n");
	printf("		\t�U                 .___|_______________|___.                    �U\n");
	printf("		\t�U                  |:::  ____            |                     �U\n");
	printf("		\t�U                  |                     |                     �U\n");
	printf("		\t�U                  !_____________________!                     �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U  �����ߣ������ѧԺ         20�ƿ�3��            �ſ���      �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("		                      ��ǰʱ��:%s  ",ctime(&now) );
}
//���ѡ����� 
void Choose()
{	now = time (NULL);
	printf("\n\n\n");
	printf("		\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U    	  ~~~~~~~~~~~~~~��ѡ��������~~~~~~~~~~~~             �U\n");                                             
	printf("		\t�U                                                              �U\n");
    printf("		\t�U                        1.����Ա                              �U\n");                    
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                        2.������                              �U\n");        
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                        3.�˳�ϵͳ                            �U\n");          
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�U    	  ~~~~~~~~~~~~~~����ѡ��<1-3>~~~~~~~~~~~~              �U\n");     
	printf("		\t�U                                                              �U\n");
	printf("		\t�U                                                              �U\n");
	printf("		\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("		                      ��ǰʱ��:%s  ",ctime(&now) );	
}
//����Ա��¼��֤���� 
int Login()
{
		char pass[50];	
		char password[50]="123456";          					//���ù���Ա���� 
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t\t���������Ա����:\n");
		printf("\n\n\n\n\n\n\n");
		printf("                                                ���ڴ˴�����:");
		scanf("%s",pass);
		if(!strcmp(pass,password))		//��֤���� 
		{
		printf("\n\n\n\n\n\n\n");
		printf("===================================================��¼�ɹ���==================================================\n");
		Sleep(1500);						//��½��ʱ���򣬲������ݵĵ�½״̬	
		return 1;
		}	
		else {
		printf("\n\n\n\n\n\n\n");
		printf("============================================���������û�й���ԱȨ�ޣ�========================================\n");
		Sleep(2000);						//��½��ʱ���򣬲������ݵĵ�½״̬	
		system("cls");
		return -1;
	}
	return 0;
}


