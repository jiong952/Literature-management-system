#include "includes.h"
time_t now;//ϵͳʱ��

int main(int argc, const char** argv) {
    system("color 3e");  	//��������ɫ 
	
    int c,a;		//c,a����switch
    int i,j;		//i,j����ѭ��
	Welcome();			//��ӭ���� 
    
	system("pause");
	system("cls");

    BTree t;
    InitBTNode(t);
//    InitBTree(t);
	Init(t);
    loop:Choose();				//���ѡ�����
	printf("���������ָ��:");
    scanf("%d",&a);
	
    result r;
	while(a<1||a>3)			//�û������������б�����ʾ 
	{
		printf("���������������ȷָ��(1-3)\n");
		scanf("%d",&a);
		getchar();
	}
	system("cls");

    if(a==1)	//����Աѡ�� 
	{	
	LogRecord(Info,"�������Ա����");
		j=Login();    //��Login����ֵ��ֵ��j	
		if(j==1)	//�ɹ���¼����Ա 
		{ 	while(1)
			{ 
    		LogRecord(Info,"�������Ա����");
			Menu_manager();		//����Ա�˵� 
			printf("���������ָ��:\n");
			i=scanf("%d",&a);
			if(i!=1)				//��ֹ�û��������ĵ��³����� 
			{
			do{
				printf("���������������ȷָ��(0-11)��\n");
				i=scanf("%d",&a);
				fflush(stdin);
			  }while(i!=1);
			}
			while(a< 0||a>11)			//�û������������б�����ʾ 
			{
				printf("���������������ȷָ��(0-11)\n");
				scanf("%d",&a);
				getchar();
			}
			switch(a)
			{	
				case 1:			//�ɱ����
				{	
					LogRecord(Info,"�ɱ����");
					getchar();
					printf("********�ɱ����*********��\n");
                    printf("���������׵ı��\n");
                    int bookId;
                    scanf("%d", &bookId);
                    SearchBTree(t, bookId, r);
                    if (r.tag == 1) {
                        printf("�������Ѵ���\n");
                        ShowBook(t, bookId);
                        int bookNum1;
                        printf("��������Ҫ��Ӵ����׵�����\n");
                        scanf("%d", &bookNum1);
                        addBook(t, bookId, bookNum1);
                    }
                    else {
                        printf("�����ײ����ڣ�\n");
                        char bookName[30], bookWriter[40], bookPress[40];
                        printf("�밴˳����������׵����������ߡ������磨�ÿո������\n");
                        scanf("%s%s%s", bookName,bookWriter,bookPress);
                        printf("��������Ҫ��Ӵ����׵�����\n");
                        int bookNum2;
                        scanf("%d", &bookNum2);
                        BookType* newBook;
                        newBook = (BookType *)malloc(sizeof(BookType));
                        strcpy(newBook->bookName,bookName);
                        strcpy(newBook->writerName,bookWriter);
                        strcpy(newBook->bookPress,bookPress);
                        newBook->booknumAll = bookNum2;
                        newBook->booknumNow = bookNum2;
                        newBook->borrower = NULL;
                        InsertBook(t, bookId, newBook);
                    }
                    printf("������!\n");
                    ShowBook(t, bookId);
					system("pause");
					getchar();
					system("cls");
					break;	
				}	
                case  2 :		//������ ������ɾ��
				{	
					LogRecord(Info,"������");
					getchar();
					printf("********������*********��\n");
					printf("���������׵ı�ţ�����0���أ�:\n");
					int key02;
			        scanf("%d", &key02);
					getchar();
					while(key02 != 0)
					{	
                        SearchBTree(t, key02, r);
                        if (r.tag == 0)
                            printf("�����ײ����ڣ�\n");
                        else {
                            ShowBook(t, key02);
                            printf("��ʾ������󲻿ɻָ�����ȷ���Ƿ������\n");
                            printf("  1��ȷ�����       0��ȡ��  \n");
                            int a;
                            scanf("%d", &a);
                            if (a == 1) {
                                DeleteBook(t, key02);
                                printf("����ɹ�!\n");
                            }
                            else
                                printf("��ȡ��\n");
                        }
						system("pause");
						getchar();
						printf("���������׵ı�ţ�������ɾ�������� 0 ��:\n");
						scanf("%d", &key02);
					}
					system("cls");
					break;
				}	
				case 3:		//��������
				{	
					LogRecord(Info,"��������");
					getchar();
					printf("********��������*********��\n");
			        printf("���������׵ı��\n");
			        int key03;
			        scanf("%d", &key03);
			        SearchBTree(t, key03, r);
			        if(r.tag==0)
			            printf("�����ײ����ڣ�\n");
			        else {
			            ShowBook(t, key03);
			            if (emtyBook(r.node, r.index)){ 
			                printf("�������ֿ�治�㣬�Ƿ�ѡ��ԤԼ��\n");
			                printf("1����   0����  \n");
			                int a0;
			                scanf("%d", &a0);
			                if(a0==1){
			                	printf("���������֤�ţ�\n");
			                    int q0;
			                    scanf("%d", &q0);
			                    printf("����������������\n");
			                    char name0[20];
			                    scanf("%s", name0, sizeof(name0));
			                    if(HasBorrow(r,q0,name0)) {
			                    	//���ж��ǲ��������
									//�ǵĻ�  return error 
				                    int flag0 = 0;
				                   	Booking(r, q0, name0,&flag0);
				                    if(flag0){
				                    	printf("ԤԼ�ɹ�!\n");
									}
								}
							}
			                //�Ƿ�ԤԼ
							//ԤԼ�����1 
							} 
			            else {
			                printf("��ȷ���Ƿ�����ף�\n");
			                printf("1��ȷ��   0��ȡ��  \n");
			                int a;
			                scanf("%d", &a);
			                if (a == 1) {
			                    printf("���������֤�ţ�\n");
			                    int q;
			                    scanf("%d", &q);
			                    printf("����������������\n");
			                    char name[20];
			                    scanf("%s", name, sizeof(name));
			                    int flag = 0;
			                    BorrowBook(r, q, name,&flag);
			                    if(flag){
			                    	ShowBook(t, key03);
			                    	printf("���ĳɹ�!\n");
								}
			                }
			                else
			                    printf("��ȡ��\n");
			            }
				}
					system("pause");
					getchar();
					system("cls");
					break;
				}

				
				case  4 : 		//�黹����
				    {	
						LogRecord(Info,"�黹����");
					    getchar();
						printf("********�黹����*********��\n");
					    printf("���������׵ı��\n");
					    int key04;
					    scanf("%d", &key04);
					    SearchBTree(t, key04, r);
					    if (r.tag == 0)
					        printf("�����ײ����ڣ�\n");
					    else {
					        ShowBook(t, key04);
					        printf("��ȷ���Ƿ�黹��\n");
					        printf("1��ȷ��   0��ȡ��  \n");
					        int b;
					        scanf("%d", &b);
					        if ( b == 1) {
					            printf("���������֤�ţ�\n");
					            int q;
					            scanf("%d", &q);
					            printf("����������������\n");
					            char name[20];
					            scanf("%s", name, sizeof(name));
					            if (ReturnBook(r, q, name)) {
					            	BorrowerType *bookEr;
									bookEr = (BorrowerType *)malloc(sizeof(BorrowerType));
					            	while(CancelBooking(r,bookEr)){
					            		int flag03 = 0;
				                    	BorrowBook(r, bookEr->borrowerId, bookEr->name,&flag03);
				                    	printf("�ѽ��黹���齻��ԤԼ�� \n");
									}
					            	//while�鿴�Ƿ�����ԤԼ 
					            	//�黹�����һ
									//���黹�����е����Զ����� 
					                ShowBook(t, key04);
					            }
					            else
					                printf("�黹ʧ��!���޶�Ӧ�Ľ����ߣ�\n");
					        }
					        else
					            printf("��ȡ��\n");
					    }
						system("pause");
						getchar();
						system("cls");
						break;
					} 

				
				case  5 :		// �鿴ĳ��������Ϣ���������׽�������� 
				{	
					LogRecord(Info,"�鿴ĳ��������Ϣ���������׽�������� ");
					getchar();
                    printf("���������׵ı��\n");
                    int key05;
                    scanf("%d", &key05);
                    SearchBTree(t, key05, r);
                    if (r.tag == 0)
                        printf("�����ײ����ڣ�\n");
                    else {
                        ShowBookAll(t, key05);
                        
                    }	
					system("pause");
					getchar();
					system("cls");
					break;
				} 
				
			 	case  6 : 		//���B����״̬
				{	
					LogRecord(Info,"���B����״̬");
                    PrintBTree(t);
					system("pause");
					getchar();
					system("cls");
					break;
				}
				case  7 :		//����������� 
				{	
					LogRecord(Info,"����������� ");
					getchar();
					printf("                   |-------------------------------------------------------------------------|\n");
					printf("                   |���     ����           ����          ������            �ִ���  �ܿ���� |\n");
					TraverseBook(t);
					system("pause");
					getchar();
					system("cls");
					break;	
				}
				case  8 : 		//���������������� 
				{	
					LogRecord(Info,"����������������  ");
					getchar();
					int flag = 0;
					printf("����������������\n");
				    char name[20];
				    scanf("%s", name, sizeof(name));
					SearchByWriter(t,name,&flag);
					if(flag == 0)
						 printf("���޴�����������ף�\n");
					system("pause");
					getchar();
					system("cls");
					break;
				}
				case 9 :		//���ݽ������������� 
			    {	
					LogRecord(Info,"���ݽ�������������");
			    	printf("���������֤�ţ�\n");
				    int q;
				    scanf("%d", &q);
				    printf("����������������\n");
				    char name[20];
				    scanf("%s", name, sizeof(name));
				    int flag = 0;
				    SearchByBorrower(t,q,name,&flag);
				    if(flag == 0)
						 printf("���޽��ļ�¼��\n");
				    system("pause");
					getchar();
					system("cls");
				    break;
				}
				case  10:	//��ת��ѡ����ݲ˵� 
				{
					system("pause");
					system("cls");
					goto loop;
				}
				case 11://�������ݵ��ļ���
				{
					Save(t);
					printf("�������ݳɹ���");
					system("pause");
					getchar();
					system("cls");
					break; 
				 } 
				case  0 : 		//�˳�ϵͳ 
				{	printf("===================================================�˳��ɹ���==================================================\n");
					Sleep(500);	
					exit (0);
				}
				default:		
				{
					printf("��������ȷָ��.\n");
					break;
				}
	
			}
			
			}
		}
    } 

	else if(a==2)		//ѡ�ֲ˵�
	{
	
	while(1)
	{		
			Menu_borrower();
			LogRecord(Info,"��������߽���");
			printf("���������ָ��:\n");
			i=scanf("%d",&a);
			if(i!=1)				//��ֹ�û��������ĵ��³����� 
			{
			do{
				printf("���������������ȷָ�\n");
				i=scanf("%d",&a);
				fflush(stdin);
			  }while(i!=1);
			}
			while(a<0||a>11)
	{
		printf("���������������ȷָ��\n");
		scanf("%d",&a);
		getchar();
	}
	switch(a)
	{
		
	case 1:         //��������
	{	
		LogRecord(Info,"��������");
		getchar();
		printf("********��������*********��\n");
        printf("���������׵ı��\n");
        int key03;
        scanf("%d", &key03);
        SearchBTree(t, key03, r);
        if(r.tag==0)
            printf("�����ײ����ڣ�\n");
        else {
            ShowBook(t, key03);
            if (emtyBook(r.node, r.index)){ 
                printf("�������ֿ�治�㣬�Ƿ�ѡ��ԤԼ��\n");
                printf("1����   0����  \n");
                int a0;
                scanf("%d", &a0);
                if(a0==1){
                	printf("���������֤�ţ�\n");
                    int q0;
                    scanf("%d", &q0);
                    printf("����������������\n");
                    char name0[20];
                    scanf("%s", name0, sizeof(name0));
                    if(HasBorrow(r,q0,name0)) {
                    	//���ж��ǲ��������
						//�ǵĻ�  return error 
	                    int flag0 = 0;
	                   	Booking(r, q0, name0,&flag0);
	                    if(flag0){
	                    	printf("ԤԼ�ɹ�!\n");
						}
					}
				}
                //�Ƿ�ԤԼ
				//ԤԼ�����1 
				} 
            else {
                printf("��ȷ���Ƿ�����ף�\n");
                printf("1��ȷ��   0��ȡ��  \n");
                int a;
                scanf("%d", &a);
                if (a == 1) {
                    printf("���������֤�ţ�\n");
                    int q;
                    scanf("%d", &q);
                    printf("����������������\n");
                    char name[20];
                    scanf("%s", name, sizeof(name));
                    int flag = 0;
                    BorrowBook(r, q, name,&flag);
                    if(flag){
                    	ShowBook(t, key03);
                    	printf("���ĳɹ�!\n");
					}
                }
                else
                    printf("��ȡ��\n");
            }
	}
		system("pause");
		getchar();
		system("cls");
		break;
	}
	case  2 : 		//�黹����
    {	
		LogRecord(Info,"�黹����");
	    getchar();
		printf("********�黹����*********��\n");
	    printf("���������׵ı��\n");
	    int key04;
	    scanf("%d", &key04);
	    SearchBTree(t, key04, r);
	    if (r.tag == 0)
	        printf("�����ײ����ڣ�\n");
	    else {
	        ShowBook(t, key04);
	        printf("��ȷ���Ƿ�黹��\n");
	        printf("1��ȷ��   0��ȡ��  \n");
	        int b;
	        scanf("%d", &b);
	        if ( b == 1) {
	            printf("���������֤�ţ�\n");
	            int q;
	            scanf("%d", &q);
	            printf("����������������\n");
	            char name[20];
	            scanf("%s", name, sizeof(name));
	            if (ReturnBook(r, q, name)) {
	            	BorrowerType *bookEr;
					bookEr = (BorrowerType *)malloc(sizeof(BorrowerType));
	            	while(CancelBooking(r,bookEr)){
	            		int flag03 = 0;
                    	BorrowBook(r, bookEr->borrowerId, bookEr->name,&flag03);
                    	printf("�ѽ��黹���齻��ԤԼ�� \n");
					}
	            	//while�鿴�Ƿ�����ԤԼ 
	            	//�黹�����һ
					//���黹�����е����Զ����� 
	                ShowBook(t, key04);
	            }
	            else
	                printf("�黹ʧ��!���޶�Ӧ�Ľ����ߣ�\n");
	        }
	        else
	            printf("��ȡ��\n");
	    }
		system("pause");
		getchar();
		system("cls");
		break;
	} 

    case  3 :		// �鿴ĳ��������Ϣ
    {	
		LogRecord(Info,"�鿴ĳ��������Ϣ");
		getchar();
        printf("��������ı��\n");
        int key05;
        scanf("%d", &key05);
        SearchBTree(t, key05, r);
        if (r.tag == 0)
            printf("���鱾�����ڣ�\n");
        else {
            ShowBook(t, key05);
            
        }	
        system("pause");
        getchar();
        system("cls");
        break;
    } 
    case  4 : 		//���B����״̬
    {	
		LogRecord(Info,"���B����״̬");
        PrintBTree(t);
        system("pause");
        getchar();
        system("cls");
        break;
    }

    case  5 :		//����������� 
		{	
			LogRecord(Info,"����������� ");
			getchar();
			printf("                   |-------------------------------------------------------------------------|\n");
			printf("                   |���     ����           ����          ������            �ִ���  �ܿ���� |\n");
			TraverseBook(t);
			system("pause");
			getchar();
			system("cls");
			break;	
		}
		
	case 6 :		//���ݽ������������� 
    {	
		LogRecord(Info,"���ݽ������������� ");
    	printf("���������֤�ţ�\n");
	    int q;
	    scanf("%d", &q);
	    printf("����������������\n");
	    char name[20];
	    scanf("%s", name, sizeof(name));
	    int flag = 0;
	    SearchByBorrower(t,q,name,&flag);
		if(flag == 0)
			printf("���޽��ļ�¼��\n");
	    system("pause");
		getchar();
		system("cls");
	    break;
	}
		case  7 : 		//���������������� 
	{	
		LogRecord(Info,"����������������  ");
		getchar();
		int flag = 0;
		printf("����������������\n");
	    char name[20];
	    scanf("%s", name, sizeof(name));
		SearchByWriter(t,name,&flag);
		if(flag == 0)
			 printf("���޴�����������ף�\n");
		system("pause");
		getchar();
		system("cls");
		break;
	}
	case 9:				//����ѡ��˵����� 
	{
		system("pause");
		system("cls");
		goto loop;
	}
	case 10://�������ݵ��ļ���
{
	Save(t);
	printf("�������ݳɹ���");
	system("pause");
	getchar();
	system("cls");
	break; 
 } 
	case 0:  //�˳�ϵͳ 
	{
		printf("===================================================�ɹ��˳�ϵͳ==================================================\n");
		Sleep(500);
		return 0 ;
	}
	default:
	{
		printf("��������ȷָ��.\n");
		break;
	}
		
	}
	
	} 
	}

	getchar();
    return 0;
}


