#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>
using namespace std;

#define m 4                     //B���Ľ�
#define MAX_NUM m               //�ؼ�������
#define MIN_NUM (m-1)/2         //��ͷ�����ؼ�������
#define SPLIT_INDEX (m+1)/2     //���Ѵ��±�
extern time_t now;//ϵͳʱ��

enum {Error,Waring,Info,Debug};
 
//�궨����־
#define LogRecord(_error_level,_fmt,_X...) \
    do { \
        time_t _current_time=time(NULL); \
        char _file_name[256]="\0"; \
        strftime(_file_name,sizeof(_file_name),"%Y-%m-%d_LOG_RECORD.log",localtime(&_current_time)); \
        FILE *_fp=NULL; \
        _fp=fopen(_file_name,"a+"); \
        if(_fp!=NULL) \
        { \
            char _time_str[32]; \
            strftime(_time_str,sizeof(_time_str),"%Y-%m-%d %H:%M:%S",localtime(&_current_time)); \
            if(_error_level==Error) \
            { \
                fprintf(_fp,"[%s]-[%s]-[%s]-[%d] :> "_fmt"\n",_time_str,"Error",__FILE__,__LINE__,##_X); \
            } \
            else if(_error_level==Waring) \
            { \
                fprintf(_fp,"[%s]-[%s]-[%s]-[%d] :> "_fmt"\n",_time_str,"Waring",__FILE__,__LINE__,##_X); \
            } \
            else if(_error_level==Info) \
            { \
                fprintf(_fp,"[%s]-[%s]-[%s]-[%d] :> "_fmt"\n",_time_str,"Info",__FILE__,__LINE__,##_X); \
            } \
            else if(_error_level==Debug) \
            { \
                fprintf(_fp,"[%s]-[%s]-[%s]-[%d] :> "_fmt"\n",_time_str,"Debug",__FILE__,__LINE__,##_X); \
            } \
            fclose(_fp); \
        } \
    }while(0);


typedef int KeyType; //���BookId����

typedef struct Borrower{
    int borrowerId;   //������ͼ��֤��
    char name[20];  //����������
    time_t time;   //�黹ʱ��
    struct  Borrower *next;     //��������Ϣ������
}BorrowerType; //����������

typedef struct {
	char bookName[30];   //����
	char writerName[20]; //����
	char bookPress[30];  //������
	int booknumNow;    //�ִ���
	int booknumAll;    //�ܿ����
	BorrowerType * borrower;
	BorrowerType * booker;
}BookType;  //��������


typedef struct BTNode{
    int keynum;                 //��㵱ǰ�Ĺؼ��ָ���
    int key[m+1];               //��������,key[0]����
    struct BTNode* parent;      //˫�׽��ָ��
    struct BTNode* ptr[m+1];    //���ӽ��ָ������
    BookType* books[m+1];         //�鱾����,books[0]����
}BTNode, *BTree;

typedef struct{
    int index;          //1<=index<=m,�ڽ���еĹؼ���λ��
    int tag;            //1:���ҳɹ���0������ʧ��
    BTNode* node;         //ָ���ҵ��Ľ��
}result;




//ͼ�����Ĳ����ӿ�
void InsertBook(BTree &T, int k, BookType* book);  //�ɱ����
void DeleteBook(BTree &t, KeyType key);                                          //������
void BorrowBook(result r,int number,char *name,int *flag);                              //����ͼ��
int  HasBorrow(result r,int number,char *name);	//�ж��Ƿ���  0��ʾ��� 
int ReturnBook(result r, int number, char *name);                          //�黹ͼ��
void ShowBookAll(BTree t, KeyType key);                                      //�鿴ĳ��ͼ�����Ϣ�����������ߣ�
int SearchByWriter(BTree t,char *name, int *flag);    //����������������
int SearchByBorrower(BTree t,int number,char *name, int *flag);    //���ݽ�������������
void ShowBook(BTree t, KeyType key); //���ĳ�������Ϣ
void addBook(BTree t, KeyType key, int num); //���ĳ���������
int emtyBook(BTree q, int i); 		//���ĳ������ִ����Ƿ����0
void TraverseBook(BTree t);			//�����������������Ϣ
void Booking(result r,int number,char *name,int *flag);//ԤԼ���� 
int CancelBooking(result r,BorrowerType *booker);//ԤԼ���׼�ȥ 1���ɹ� 
//����չʾ
void Welcome();         //��ӭ����
void Choose();          //���ѡ�����
int Login();            //����Ա��¼��֤���� 
void Menu_manager();    //����Ա�˵�
void Menu_borrower();    //�����߲˵�


//insert
void InitBTree(BTree &t);       //��ʼ����
void InitBTNode(BTree &p);      //��ʼ�����
int InsertBTree(BTree &T, int k, BookType* book);   //������
void split(BTree &q, BTree &ap);    //���ѱ��ͽ��
void newRoot(BTree &T, BTree p, BTree ap, int k, BookType* book);   //�����¸����
void Insert(BTree &q, int k, int index, BTree ap, BookType* book);  //����ؼ��ּ�ָ��ap


//delete
int DeleteBTree(BTree &T, int key);         //ɾ������Ϊkey�ļ�¼
void Successor(BTree &node, int &index);    //�������ն˽�㣬��ֱ��ǰ����������ֵ���ǵ���ǰ���
int Remove(BTree& node, int i);     //�ӽ��p��ɾ��key[i]
int InsertBookType(BTree& node, int key,int i, BookType* book);   //�򸸽�����ؼ���
void Restore(BTree& node, int index);   //������
void CombineBTNode(BTree& l_node, BTree& r_node);   //�ϲ����
void DeleteRoot(BTree& root);   //���ϲ����������м�¼���뵽���ڵ���

//print
void Traverse(BTree t, int k); //����B��
void PrintBTree(BTree t);   //��ӡB��


//search
void SearchBTree(BTree T, int k, result &r);    //��m��B��t�ϲ�������k����r����(pt,i,tag)
int Search(BTree p, int k); //��p->key[1..p->keynum]�в���p->key[i-1]<k<=p->key[i]

//data
void log_reocrd(int error_level, const char *format, ...);	//��־��¼ 
void Init(BTree &t); //��ȡͼ���ļ�
void Save(BTree &T);
void save_btree(BTree &T, FILE* fp); 
