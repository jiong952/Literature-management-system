#include "includes.h"
time_t now;//系统时间

int main(int argc, const char** argv) {
    system("color 3e");  	//背景淡蓝色 
	
    int c,a;		//c,a用于switch
    int i,j;		//i,j用于循环
	Welcome();			//欢迎界面 
    
	system("pause");
	system("cls");

    BTree t;
    InitBTNode(t);
//    InitBTree(t);
	Init(t);
    loop:Choose();				//身份选择界面
	printf("请输入你的指令:");
    scanf("%d",&a);
	
    result r;
	while(a<1||a>3)			//用户错误输入后进行报错提示 
	{
		printf("输入错误！请输入正确指令(1-3)\n");
		scanf("%d",&a);
		getchar();
	}
	system("cls");

    if(a==1)	//管理员选项 
	{	
	LogRecord(Info,"进入管理员界面");
		j=Login();    //把Login返回值赋值给j	
		if(j==1)	//成功登录管理员 
		{ 	while(1)
			{ 
    		LogRecord(Info,"进入管理员界面");
			Menu_manager();		//管理员菜单 
			printf("请输入你的指令:\n");
			i=scanf("%d",&a);
			if(i!=1)				//防止用户输入中文导致程序奔溃 
			{
			do{
				printf("输入错误，请输入正确指令(0-11)！\n");
				i=scanf("%d",&a);
				fflush(stdin);
			  }while(i!=1);
			}
			while(a< 0||a>11)			//用户错误输入后进行报错提示 
			{
				printf("输入错误！请输入正确指令(0-11)\n");
				scanf("%d",&a);
				getchar();
			}
			switch(a)
			{	
				case 1:			//采编入库
				{	
					LogRecord(Info,"采编入库");
					getchar();
					printf("********采编入库*********：\n");
                    printf("请输入文献的编号\n");
                    int bookId;
                    scanf("%d", &bookId);
                    SearchBTree(t, bookId, r);
                    if (r.tag == 1) {
                        printf("此文献已存在\n");
                        ShowBook(t, bookId);
                        int bookNum1;
                        printf("请输入需要添加此文献的数量\n");
                        scanf("%d", &bookNum1);
                        addBook(t, bookId, bookNum1);
                    }
                    else {
                        printf("此文献不存在，\n");
                        char bookName[30], bookWriter[40], bookPress[40];
                        printf("请按顺序输入此文献的书名、作者、出版社（用空格隔开）\n");
                        scanf("%s%s%s", bookName,bookWriter,bookPress);
                        printf("请输入需要添加此文献的数量\n");
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
                    printf("添加完成!\n");
                    ShowBook(t, bookId);
					system("pause");
					getchar();
					system("cls");
					break;	
				}	
                case  2 :		//清除库存 允许多次删除
				{	
					LogRecord(Info,"清除库存");
					getchar();
					printf("********清除库存*********：\n");
					printf("请输入文献的编号（输入0返回）:\n");
					int key02;
			        scanf("%d", &key02);
					getchar();
					while(key02 != 0)
					{	
                        SearchBTree(t, key02, r);
                        if (r.tag == 0)
                            printf("此文献不存在！\n");
                        else {
                            ShowBook(t, key02);
                            printf("提示：清除后不可恢复！请确认是否清除：\n");
                            printf("  1：确认清除       0：取消  \n");
                            int a;
                            scanf("%d", &a);
                            if (a == 1) {
                                DeleteBook(t, key02);
                                printf("清除成功!\n");
                            }
                            else
                                printf("已取消\n");
                        }
						system("pause");
						getchar();
						printf("请输入文献的编号（不继续删除请输入 0 ）:\n");
						scanf("%d", &key02);
					}
					system("cls");
					break;
				}	
				case 3:		//借阅文献
				{	
					LogRecord(Info,"借阅文献");
					getchar();
					printf("********借阅文献*********：\n");
			        printf("请输入文献的编号\n");
			        int key03;
			        scanf("%d", &key03);
			        SearchBTree(t, key03, r);
			        if(r.tag==0)
			            printf("此文献不存在！\n");
			        else {
			            ShowBook(t, key03);
			            if (emtyBook(r.node, r.index)){ 
			                printf("此文献现库存不足，是否选择预约！\n");
			                printf("1：是   0：否  \n");
			                int a0;
			                scanf("%d", &a0);
			                if(a0==1){
			                	printf("请输入借阅证号：\n");
			                    int q0;
			                    scanf("%d", &q0);
			                    printf("请输入您的姓名：\n");
			                    char name0[20];
			                    scanf("%s", name0, sizeof(name0));
			                    if(HasBorrow(r,q0,name0)) {
			                    	//先判断是不是他借的
									//是的话  return error 
				                    int flag0 = 0;
				                   	Booking(r, q0, name0,&flag0);
				                    if(flag0){
				                    	printf("预约成功!\n");
									}
								}
							}
			                //是否预约
							//预约链表加1 
							} 
			            else {
			                printf("请确认是否借文献：\n");
			                printf("1：确认   0：取消  \n");
			                int a;
			                scanf("%d", &a);
			                if (a == 1) {
			                    printf("请输入借阅证号：\n");
			                    int q;
			                    scanf("%d", &q);
			                    printf("请输入您的姓名：\n");
			                    char name[20];
			                    scanf("%s", name, sizeof(name));
			                    int flag = 0;
			                    BorrowBook(r, q, name,&flag);
			                    if(flag){
			                    	ShowBook(t, key03);
			                    	printf("借阅成功!\n");
								}
			                }
			                else
			                    printf("已取消\n");
			            }
				}
					system("pause");
					getchar();
					system("cls");
					break;
				}

				
				case  4 : 		//归还文献
				    {	
						LogRecord(Info,"归还文献");
					    getchar();
						printf("********归还文献*********：\n");
					    printf("请输入文献的编号\n");
					    int key04;
					    scanf("%d", &key04);
					    SearchBTree(t, key04, r);
					    if (r.tag == 0)
					        printf("此文献不存在！\n");
					    else {
					        ShowBook(t, key04);
					        printf("请确认是否归还：\n");
					        printf("1：确认   0：取消  \n");
					        int b;
					        scanf("%d", &b);
					        if ( b == 1) {
					            printf("请输入借阅证号：\n");
					            int q;
					            scanf("%d", &q);
					            printf("请输入您的姓名：\n");
					            char name[20];
					            scanf("%s", name, sizeof(name));
					            if (ReturnBook(r, q, name)) {
					            	BorrowerType *bookEr;
									bookEr = (BorrowerType *)malloc(sizeof(BorrowerType));
					            	while(CancelBooking(r,bookEr)){
					            		int flag03 = 0;
				                    	BorrowBook(r, bookEr->borrowerId, bookEr->name,&flag03);
				                    	printf("已将归还的书交给预约者 \n");
									}
					            	//while查看是否有人预约 
					            	//归还链表减一
									//将归还链表中的人自动借书 
					                ShowBook(t, key04);
					            }
					            else
					                printf("归还失败!查无对应的借阅者！\n");
					        }
					        else
					            printf("已取消\n");
					    }
						system("pause");
						getchar();
						system("cls");
						break;
					} 

				
				case  5 :		// 查看某种文献信息（包括文献借阅情况） 
				{	
					LogRecord(Info,"查看某种文献信息（包括文献借阅情况） ");
					getchar();
                    printf("请输入文献的编号\n");
                    int key05;
                    scanf("%d", &key05);
                    SearchBTree(t, key05, r);
                    if (r.tag == 0)
                        printf("此文献不存在！\n");
                    else {
                        ShowBookAll(t, key05);
                        
                    }	
					system("pause");
					getchar();
					system("cls");
					break;
				} 
				
			 	case  6 : 		//输出B树的状态
				{	
					LogRecord(Info,"输出B树的状态");
                    PrintBTree(t);
					system("pause");
					getchar();
					system("cls");
					break;
				}
				case  7 :		//输出所有文献 
				{	
					LogRecord(Info,"输出所有文献 ");
					getchar();
					printf("                   |-------------------------------------------------------------------------|\n");
					printf("                   |书号     书名           作者          出版社            现存量  总库存量 |\n");
					TraverseBook(t);
					system("pause");
					getchar();
					system("cls");
					break;	
				}
				case  8 : 		//按作者名查阅文献 
				{	
					LogRecord(Info,"按作者名查阅文献  ");
					getchar();
					int flag = 0;
					printf("请输入作者姓名：\n");
				    char name[20];
				    scanf("%s", name, sizeof(name));
					SearchByWriter(t,name,&flag);
					if(flag == 0)
						 printf("查无此作者相关文献！\n");
					system("pause");
					getchar();
					system("cls");
					break;
				}
				case 9 :		//根据借阅者搜索文献 
			    {	
					LogRecord(Info,"根据借阅者搜索文献");
			    	printf("请输入借阅证号：\n");
				    int q;
				    scanf("%d", &q);
				    printf("请输入您的姓名：\n");
				    char name[20];
				    scanf("%s", name, sizeof(name));
				    int flag = 0;
				    SearchByBorrower(t,q,name,&flag);
				    if(flag == 0)
						 printf("查无借阅记录！\n");
				    system("pause");
					getchar();
					system("cls");
				    break;
				}
				case  10:	//跳转回选择身份菜单 
				{
					system("pause");
					system("cls");
					goto loop;
				}
				case 11://保存数据到文件中
				{
					Save(t);
					printf("保存数据成功！");
					system("pause");
					getchar();
					system("cls");
					break; 
				 } 
				case  0 : 		//退出系统 
				{	printf("===================================================退出成功！==================================================\n");
					Sleep(500);	
					exit (0);
				}
				default:		
				{
					printf("请输入正确指令.\n");
					break;
				}
	
			}
			
			}
		}
    } 

	else if(a==2)		//选手菜单
	{
	
	while(1)
	{		
			Menu_borrower();
			LogRecord(Info,"进入借阅者界面");
			printf("请输入你的指令:\n");
			i=scanf("%d",&a);
			if(i!=1)				//防止用户输入中文导致程序奔溃 
			{
			do{
				printf("输入错误，请输入正确指令！\n");
				i=scanf("%d",&a);
				fflush(stdin);
			  }while(i!=1);
			}
			while(a<0||a>11)
	{
		printf("输入错误！请输入正确指令\n");
		scanf("%d",&a);
		getchar();
	}
	switch(a)
	{
		
	case 1:         //借阅文献
	{	
		LogRecord(Info,"借阅文献");
		getchar();
		printf("********借阅文献*********：\n");
        printf("请输入文献的编号\n");
        int key03;
        scanf("%d", &key03);
        SearchBTree(t, key03, r);
        if(r.tag==0)
            printf("此文献不存在！\n");
        else {
            ShowBook(t, key03);
            if (emtyBook(r.node, r.index)){ 
                printf("此文献现库存不足，是否选择预约！\n");
                printf("1：是   0：否  \n");
                int a0;
                scanf("%d", &a0);
                if(a0==1){
                	printf("请输入借阅证号：\n");
                    int q0;
                    scanf("%d", &q0);
                    printf("请输入您的姓名：\n");
                    char name0[20];
                    scanf("%s", name0, sizeof(name0));
                    if(HasBorrow(r,q0,name0)) {
                    	//先判断是不是他借的
						//是的话  return error 
	                    int flag0 = 0;
	                   	Booking(r, q0, name0,&flag0);
	                    if(flag0){
	                    	printf("预约成功!\n");
						}
					}
				}
                //是否预约
				//预约链表加1 
				} 
            else {
                printf("请确认是否借文献：\n");
                printf("1：确认   0：取消  \n");
                int a;
                scanf("%d", &a);
                if (a == 1) {
                    printf("请输入借阅证号：\n");
                    int q;
                    scanf("%d", &q);
                    printf("请输入您的姓名：\n");
                    char name[20];
                    scanf("%s", name, sizeof(name));
                    int flag = 0;
                    BorrowBook(r, q, name,&flag);
                    if(flag){
                    	ShowBook(t, key03);
                    	printf("借阅成功!\n");
					}
                }
                else
                    printf("已取消\n");
            }
	}
		system("pause");
		getchar();
		system("cls");
		break;
	}
	case  2 : 		//归还文献
    {	
		LogRecord(Info,"归还文献");
	    getchar();
		printf("********归还文献*********：\n");
	    printf("请输入文献的编号\n");
	    int key04;
	    scanf("%d", &key04);
	    SearchBTree(t, key04, r);
	    if (r.tag == 0)
	        printf("此文献不存在！\n");
	    else {
	        ShowBook(t, key04);
	        printf("请确认是否归还：\n");
	        printf("1：确认   0：取消  \n");
	        int b;
	        scanf("%d", &b);
	        if ( b == 1) {
	            printf("请输入借阅证号：\n");
	            int q;
	            scanf("%d", &q);
	            printf("请输入您的姓名：\n");
	            char name[20];
	            scanf("%s", name, sizeof(name));
	            if (ReturnBook(r, q, name)) {
	            	BorrowerType *bookEr;
					bookEr = (BorrowerType *)malloc(sizeof(BorrowerType));
	            	while(CancelBooking(r,bookEr)){
	            		int flag03 = 0;
                    	BorrowBook(r, bookEr->borrowerId, bookEr->name,&flag03);
                    	printf("已将归还的书交给预约者 \n");
					}
	            	//while查看是否有人预约 
	            	//归还链表减一
					//将归还链表中的人自动借书 
	                ShowBook(t, key04);
	            }
	            else
	                printf("归还失败!查无对应的借阅者！\n");
	        }
	        else
	            printf("已取消\n");
	    }
		system("pause");
		getchar();
		system("cls");
		break;
	} 

    case  3 :		// 查看某种文献信息
    {	
		LogRecord(Info,"查看某种文献信息");
		getchar();
        printf("请输入书的编号\n");
        int key05;
        scanf("%d", &key05);
        SearchBTree(t, key05, r);
        if (r.tag == 0)
            printf("此书本不存在！\n");
        else {
            ShowBook(t, key05);
            
        }	
        system("pause");
        getchar();
        system("cls");
        break;
    } 
    case  4 : 		//输出B树的状态
    {	
		LogRecord(Info,"输出B树的状态");
        PrintBTree(t);
        system("pause");
        getchar();
        system("cls");
        break;
    }

    case  5 :		//输出所有文献 
		{	
			LogRecord(Info,"输出所有文献 ");
			getchar();
			printf("                   |-------------------------------------------------------------------------|\n");
			printf("                   |书号     书名           作者          出版社            现存量  总库存量 |\n");
			TraverseBook(t);
			system("pause");
			getchar();
			system("cls");
			break;	
		}
		
	case 6 :		//根据借阅者搜索文献 
    {	
		LogRecord(Info,"根据借阅者搜索文献 ");
    	printf("请输入借阅证号：\n");
	    int q;
	    scanf("%d", &q);
	    printf("请输入您的姓名：\n");
	    char name[20];
	    scanf("%s", name, sizeof(name));
	    int flag = 0;
	    SearchByBorrower(t,q,name,&flag);
		if(flag == 0)
			printf("查无借阅记录！\n");
	    system("pause");
		getchar();
		system("cls");
	    break;
	}
		case  7 : 		//按作者名查阅文献 
	{	
		LogRecord(Info,"按作者名查阅文献  ");
		getchar();
		int flag = 0;
		printf("请输入作者姓名：\n");
	    char name[20];
	    scanf("%s", name, sizeof(name));
		SearchByWriter(t,name,&flag);
		if(flag == 0)
			 printf("查无此作者相关文献！\n");
		system("pause");
		getchar();
		system("cls");
		break;
	}
	case 9:				//返回选择菜单界面 
	{
		system("pause");
		system("cls");
		goto loop;
	}
	case 10://保存数据到文件中
{
	Save(t);
	printf("保存数据成功！");
	system("pause");
	getchar();
	system("cls");
	break; 
 } 
	case 0:  //退出系统 
	{
		printf("===================================================成功退出系统==================================================\n");
		Sleep(500);
		return 0 ;
	}
	default:
	{
		printf("请输入正确指令.\n");
		break;
	}
		
	}
	
	} 
	}

	getchar();
    return 0;
}


