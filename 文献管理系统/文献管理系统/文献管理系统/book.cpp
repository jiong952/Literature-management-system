#include "includes.h"

//�ɱ����
void InsertBook(BTree &T, int k, BookType* book) {
	LogRecord(Info,"�ɱ����");
	InsertBTree(T, k, book);
}
//������
void DeleteBook(BTree &t, KeyType key) {
	LogRecord(Info,"������");
	DeleteBTree(t, key);
}
//��������
void BorrowBook(result r,int number,char *name,int *flag) {
	LogRecord(Info,"��������");
	now = time (NULL)+2592000;	//������Ϊ1���� 
	BorrowerType *borrower;
	borrower = (BorrowerType *)malloc(sizeof(BorrowerType));
	strcpy(borrower->name, name);
	borrower->borrowerId = number;
	borrower->time = now;
	//�����Ƿ���
	if(!HasBorrow(r,number,name)) return ; 
	//������洢��������Ϣ 
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
//�ж��Ƿ���  0:��� 
int  HasBorrow(result r,int number,char *name){
	LogRecord(Info,"�ж��Ƿ���  0:���");
	BorrowerType *p1,*p;
	p1 = r.node->books[r.index]->borrower;
	p = p1;
	while (p1 != NULL && (p1->borrowerId != number || strcmp(p1->name,name))) {
		p = p1;
		p1 = p1->next;
	}
	if(p1!=NULL){
		printf("���ѽ��Ĵ��飬���ȹ黹!\n");
		return 0;
	}
	return 1;
}
//�黹����
int ReturnBook(result r, int number, char *name) {
	LogRecord(Info,"�黹����");
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
		//�ж��Ƿ�ʱ�黹ͼ�� 
		if(now<r.node->books[r.index]->borrower->time){
			printf("���������ڹ黹�ɹ�!\n");
		}else{
			printf("δ����Ч���ڹ黹!\n");
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

//ԤԼ���� 
void Booking(result r,int number,char *name,int *flag){
	LogRecord(Info,"ԤԼ����");
	now = time (NULL);	
	BorrowerType *booker;
	booker = (BorrowerType *)malloc(sizeof(BorrowerType));
	
	strcpy(booker->name, name);
	booker->borrowerId = number;
	booker->time = now;
	//�����Ƿ�ԤԼ��
	BorrowerType *p1,*p;
	p1 = r.node->books[r.index]->booker;
	p = p1;
	while (p1 != NULL && (p1->borrowerId != number || strcmp(p1->name,name))) {
		p = p1;
		p1 = p1->next;
	}
	if(p1!=NULL){
		printf("����ԤԼ���飬���ȹ黹!\n");
		return ;
	}
	//������洢ԤԼ����Ϣ 
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
//ԤԼ���׼�ȥ 
int CancelBooking(result r,BorrowerType *bookEr){
	LogRecord(Info,"ԤԼ���׼�ȥ ");
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
//���ĳ�����׵�ȫ����Ϣ�����������ߣ�
void ShowBookAll(BTree t, KeyType key) {
	LogRecord(Info,"���ĳ�����׵�ȫ����Ϣ�����������ߣ�");
	ShowBook(t, key);
	result r;
	SearchBTree(t, key, r);
	BorrowerType *q;
	q = r.node->books[r.index]->borrower;
	while (q != NULL) {
		printf("                   |����֤�ţ�%d, ������%s, ��ٻ���ʱ��Ϊ��%s\n",q->borrowerId,q->name,ctime(&q->time));
		printf("                   |-------------------------------------------------------------------------|\n");
		q = q->next;
	}
}
//���ĳ�����׵���Ϣ�������������ߣ�
void ShowBook(BTree t,KeyType key) {
	LogRecord(Info,"���ĳ�����׵���Ϣ�������������ߣ�");
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) {
		printf("                   |-------------------------------------------------------------------------|\n");
		printf("                   |���     ����           ����          ������            �ִ���  �ܿ���� |\n");
		printf("                   |-------------------------------------------------------------------------|\n");
		printf("                   |%d       %s           %s        %s    %d      %d     |\n", r.node->key[r.index], r.node->books[r.index]->bookName,
			r.node->books[r.index]->writerName, r.node->books[r.index]->bookPress, r.node->books[r.index]->booknumNow, r.node->books[r.index]->booknumAll);
		printf("                   |-------------------------------------------------------------------------|\n");
	}
}
//���ĳ���������
void addBook(BTree t, KeyType key, int num) {
	LogRecord(Info,"���ĳ���������");
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) {
		r.node->books[r.index]->booknumNow = r.node->books[r.index]->booknumNow + num;
		r.node->books[r.index]->booknumAll = r.node->books[r.index]->booknumAll + num;
	}
}
//���ĳ������ִ����Ƿ����0
int emtyBook(BTree q, int i) {
	LogRecord(Info,"���ĳ������ִ����Ƿ����0");
	if (q->books[i]->booknumNow >= 1)
		return 0;
	return 1;
}
//�����������������Ϣ
void TraverseBook(BTree t)
{
	LogRecord(Info,"�����������������Ϣ");
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

//����������������
int SearchByWriter(BTree t,char *name, int *flag){
	LogRecord(Info,"����������������");
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
//���ݽ������������� 
int SearchByBorrower(BTree t,int number,char *name, int *flag){
	LogRecord(Info,"���ݽ������������� ");
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
				printf("                   |����֤�ţ�%d, ������%s, ��ٻ���ʱ��Ϊ��%s\n",q->borrowerId,q->name,ctime(&q->time));
				printf("                   |-------------------------------------------------------------------------|\n");
				*flag = 1;
			}
			SearchByBorrower(t->ptr[j],number,name,flag);
		}
	}
	return *flag;
}







