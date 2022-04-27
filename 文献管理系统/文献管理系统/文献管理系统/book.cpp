#include "includes.h"

//采编入库
void InsertBook(BTree &T, int k, BookType* book) {
	LogRecord(Info,"采编入库");
	InsertBTree(T, k, book);
}
//清除库存
void DeleteBook(BTree &t, KeyType key) {
	LogRecord(Info,"清除库存");
	DeleteBTree(t, key);
}
//借阅文献
void BorrowBook(result r,int number,char *name,int *flag) {
	LogRecord(Info,"借阅文献");
	now = time (NULL)+2592000;	//借书期为1个月 
	BorrowerType *borrower;
	borrower = (BorrowerType *)malloc(sizeof(BorrowerType));
	strcpy(borrower->name, name);
	borrower->borrowerId = number;
	borrower->time = now;
	//查阅是否借过
	if(!HasBorrow(r,number,name)) return ; 
	//用链表存储借阅者信息 
	BorrowerType *q;
	q = r.node->books[r.index]->borrower;
	if (q == NULL) {
		r.node->books[r.index]->borrower = borrower;
		borrower->next = NULL;
	}
	else {
		borrower->next = r.node->books[r.index]->borrower;
		r.node->books[r.index]->borrower = borrower;
	}
	r.node->books[r.index]->booknumNow--;
	*flag = 1;
}
//判断是否借过  0:借过 
int  HasBorrow(result r,int number,char *name){
	LogRecord(Info,"判断是否借过  0:借过");
	BorrowerType *p1,*p;
	p1 = r.node->books[r.index]->borrower;
	p = p1;
	while (p1 != NULL && (p1->borrowerId != number || strcmp(p1->name,name))) {
		p = p1;
		p1 = p1->next;
	}
	if(p1!=NULL){
		printf("您已借阅此书，请先归还!\n");
		return 0;
	}
	return 1;
}
//归还文献
int ReturnBook(result r, int number, char *name) {
	LogRecord(Info,"归还文献");
	BorrowerType *q,*p;
	q = r.node->books[r.index]->borrower;
	p = q;
	while (q != NULL && (q->borrowerId != number || strcmp(q->name,name))) {
		p = q;
		q = q->next;
	}
	if (q == NULL) {
		return 0;
	}
	else {
		now = time (NULL);
		//判断是否按时归还图书 
		if(now<r.node->books[r.index]->borrower->time){
			printf("在有限期内归还成功!\n");
		}else{
			printf("未在有效期内归还!\n");
		}	
		if (q == r.node->books[r.index]->borrower)
			r.node->books[r.index]->borrower = q->next;
		else 
			p->next = q->next;
		free(q);
		r.node->books[r.index]->booknumNow++;
	}
    return 1;
}

//预约文献 
void Booking(result r,int number,char *name,int *flag){
	LogRecord(Info,"预约文献");
	now = time (NULL);	
	BorrowerType *booker;
	booker = (BorrowerType *)malloc(sizeof(BorrowerType));
	
	strcpy(booker->name, name);
	booker->borrowerId = number;
	booker->time = now;
	//查阅是否预约过
	BorrowerType *p1,*p;
	p1 = r.node->books[r.index]->booker;
	p = p1;
	while (p1 != NULL && (p1->borrowerId != number || strcmp(p1->name,name))) {
		p = p1;
		p1 = p1->next;
	}
	if(p1!=NULL){
		printf("您已预约此书，请先归还!\n");
		return ;
	}
	//用链表存储预约者信息 
	BorrowerType *q;
	q = r.node->books[r.index]->booker;
	if (q == NULL) {
		r.node->books[r.index]->booker = booker;
		booker->next = NULL;
	}
	else {
		booker->next = r.node->books[r.index]->booker;
		r.node->books[r.index]->booker = booker;
	}
	*flag = 1;
}
//预约文献减去 
int CancelBooking(result r,BorrowerType *bookEr){
	LogRecord(Info,"预约文献减去 ");
	BorrowerType *q;
	q = r.node->books[r.index]->booker;
	if (q == NULL) {
		return 0;
	}
	while(q->next!=NULL){
		q=q->next;
	}
	if(r.node->books[r.index]->booknumNow){
			
		bookEr->borrowerId = q->borrowerId;
		strcpy(bookEr->name,q->name);
		bookEr->time = q->time;
		free(q);
		return 1;
		
	}
    return 0;
}
//输出某本文献的全部信息（包括借阅者）
void ShowBookAll(BTree t, KeyType key) {
	LogRecord(Info,"输出某本文献的全部信息（包括借阅者）");
	ShowBook(t, key);
	result r;
	SearchBTree(t, key, r);
	BorrowerType *q;
	q = r.node->books[r.index]->borrower;
	while (q != NULL) {
		printf("                   |借阅证号：%d, 姓名：%s, 最迟还书时间为：%s\n",q->borrowerId,q->name,ctime(&q->time));
		printf("                   |-------------------------------------------------------------------------|\n");
		q = q->next;
	}
}
//输出某本文献的信息（不包括借阅者）
void ShowBook(BTree t,KeyType key) {
	LogRecord(Info,"输出某本文献的信息（不包括借阅者）");
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) {
		printf("                   |-------------------------------------------------------------------------|\n");
		printf("                   |书号     书名           作者          出版社            现存量  总库存量 |\n");
		printf("                   |-------------------------------------------------------------------------|\n");
		printf("                   |%d       %s           %s        %s    %d      %d     |\n", r.node->key[r.index], r.node->books[r.index]->bookName,
			r.node->books[r.index]->writerName, r.node->books[r.index]->bookPress, r.node->books[r.index]->booknumNow, r.node->books[r.index]->booknumAll);
		printf("                   |-------------------------------------------------------------------------|\n");
	}
}
//添加某本书的数量
void addBook(BTree t, KeyType key, int num) {
	LogRecord(Info,"添加某本书的数量");
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) {
		r.node->books[r.index]->booknumNow = r.node->books[r.index]->booknumNow + num;
		r.node->books[r.index]->booknumAll = r.node->books[r.index]->booknumAll + num;
	}
}
//检查某本书的现存量是否大于0
int emtyBook(BTree q, int i) {
	LogRecord(Info,"检查某本书的现存量是否大于0");
	if (q->books[i]->booknumNow >= 1)
		return 0;
	return 1;
}
//遍历输出所有文献信息
void TraverseBook(BTree t)
{
	LogRecord(Info,"遍历输出所有文献信息");
	if(t == NULL)
		return;
	if(t){
		TraverseBook(t->ptr[0]);
		for(int j=1;j<=t->keynum;j++){
			printf("                   |-------------------------------------------------------------------------|\n");
			printf("                   |%d     %s      %s     %s        %d     %d     |\n", t->key[j], t->books[j]->bookName,
			t->books[j]->writerName, t->books[j]->bookPress, t->books[j]->booknumNow, t->books[j]->booknumAll);
			printf("                   |-------------------------------------------------------------------------|\n");
			TraverseBook(t->ptr[j]);
		}
	}
	
}

//根据作者搜索书名
int SearchByWriter(BTree t,char *name, int *flag){
	LogRecord(Info,"根据作者搜索书名");
	if(t == NULL)
		return 0;
	if(t){
		SearchByWriter(t->ptr[0],name,flag);
		for(int j=1;j<=t->keynum;j++){
			if(!strcmp(t->books[j]->writerName,name)){
				printf("                   |-------------------------------------------------------------------------|\n");
				printf("                   |%d     %s      %s     %s        %d     %d     |\n", t->key[j], t->books[j]->bookName,
				t->books[j]->writerName, t->books[j]->bookPress, t->books[j]->booknumNow, t->books[j]->booknumAll);
				printf("                   |-------------------------------------------------------------------------|\n");
				*flag = 1;
			}
			SearchByWriter(t->ptr[j],name,flag);
		}
	}
	return *flag;
}
//根据借阅者搜索书名 
int SearchByBorrower(BTree t,int number,char *name, int *flag){
	LogRecord(Info,"根据借阅者搜索书名 ");
	if(t == NULL)
		return 0;
	if(t){
		SearchByBorrower(t->ptr[0],number,name,flag);
		for(int j=1;j<=t->keynum;j++){
			BorrowerType *q,*p;
			q = t->books[j]->borrower;
			p = q;
			while (q != NULL && (q->borrowerId != number || strcmp(q->name,name))) {
				p = q;
				q = q->next;
			}
			if(q!=NULL){
				printf("                   |-------------------------------------------------------------------------|\n");
				printf("                   |%d     %s      %s     %s        %d     %d     |\n", t->key[j], t->books[j]->bookName,
				t->books[j]->writerName, t->books[j]->bookPress, t->books[j]->booknumNow, t->books[j]->booknumAll);
				printf("                   |-------------------------------------------------------------------------|\n");
				printf("                   |借阅证号：%d, 姓名：%s, 最迟还书时间为：%s\n",q->borrowerId,q->name,ctime(&q->time));
				printf("                   |-------------------------------------------------------------------------|\n");
				*flag = 1;
			}
			SearchByBorrower(t->ptr[j],number,name,flag);
		}
	}
	return *flag;
}







