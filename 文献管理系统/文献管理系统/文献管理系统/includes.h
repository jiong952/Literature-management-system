#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>
using namespace std;

#define m 4                     //B树的阶
#define MAX_NUM m               //关键字上限
#define MIN_NUM (m-1)/2         //除头结点外关键字下限
#define SPLIT_INDEX (m+1)/2     //分裂处下标
extern time_t now;//系统时间

enum {Error,Waring,Info,Debug};
 
//宏定义日志
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


typedef int KeyType; //书号BookId类型

typedef struct Borrower{
    int borrowerId;   //借阅者图书证号
    char name[20];  //借阅者姓名
    time_t time;   //归还时间
    struct  Borrower *next;     //借阅者信息用链表
}BorrowerType; //借阅者类型

typedef struct {
	char bookName[30];   //书名
	char writerName[20]; //作者
	char bookPress[30];  //出版社
	int booknumNow;    //现存量
	int booknumAll;    //总库存量
	BorrowerType * borrower;
	BorrowerType * booker;
}BookType;  //文献类型


typedef struct BTNode{
    int keynum;                 //结点当前的关键字个数
    int key[m+1];               //索引数组,key[0]不用
    struct BTNode* parent;      //双亲结点指针
    struct BTNode* ptr[m+1];    //孩子结点指针数组
    BookType* books[m+1];         //书本数组,books[0]不用
}BTNode, *BTree;

typedef struct{
    int index;          //1<=index<=m,在结点中的关键字位序
    int tag;            //1:查找成功，0：查找失败
    BTNode* node;         //指向找到的结点
}result;




//图书管理的操作接口
void InsertBook(BTree &T, int k, BookType* book);  //采编入库
void DeleteBook(BTree &t, KeyType key);                                          //清除库存
void BorrowBook(result r,int number,char *name,int *flag);                              //借阅图书
int  HasBorrow(result r,int number,char *name);	//判断是否借过  0表示借过 
int ReturnBook(result r, int number, char *name);                          //归还图书
void ShowBookAll(BTree t, KeyType key);                                      //查看某种图书的信息（包括借阅者）
int SearchByWriter(BTree t,char *name, int *flag);    //根据作者搜索书名
int SearchByBorrower(BTree t,int number,char *name, int *flag);    //根据借阅者搜索书名
void ShowBook(BTree t, KeyType key); //输出某本书的信息
void addBook(BTree t, KeyType key, int num); //添加某本书的数量
int emtyBook(BTree q, int i); 		//检查某本书的现存量是否大于0
void TraverseBook(BTree t);			//遍历输出所有文献信息
void Booking(result r,int number,char *name,int *flag);//预约文献 
int CancelBooking(result r,BorrowerType *booker);//预约文献减去 1：成功 
//界面展示
void Welcome();         //欢迎界面
void Choose();          //身份选择界面
int Login();            //管理员登录验证界面 
void Menu_manager();    //管理员菜单
void Menu_borrower();    //借阅者菜单


//insert
void InitBTree(BTree &t);       //初始化树
void InitBTNode(BTree &p);      //初始化结点
int InsertBTree(BTree &T, int k, BookType* book);   //插入结点
void split(BTree &q, BTree &ap);    //分裂饱和结点
void newRoot(BTree &T, BTree p, BTree ap, int k, BookType* book);   //创建新根结点
void Insert(BTree &q, int k, int index, BTree ap, BookType* book);  //插入关键字及指针ap


//delete
int DeleteBTree(BTree &T, int key);         //删除索引为key的记录
void Successor(BTree &node, int &index);    //若不是终端结点，将直接前驱的索引和值覆盖掉当前结点
int Remove(BTree& node, int i);     //从结点p中删除key[i]
int InsertBookType(BTree& node, int key,int i, BookType* book);   //向父结点插入关键字
void Restore(BTree& node, int index);   //调整树
void CombineBTNode(BTree& l_node, BTree& r_node);   //合并结点
void DeleteRoot(BTree& root);   //将合并后结点中所有记录插入到父节点中

//print
void Traverse(BTree t, int k); //遍历B树
void PrintBTree(BTree t);   //打印B树


//search
void SearchBTree(BTree T, int k, result &r);    //在m阶B树t上查找索引k，用r返回(pt,i,tag)
int Search(BTree p, int k); //在p->key[1..p->keynum]中查找p->key[i-1]<k<=p->key[i]

//data
void log_reocrd(int error_level, const char *format, ...);	//日志记录 
void Init(BTree &t); //读取图书文件
void Save(BTree &T);
void save_btree(BTree &T, FILE* fp); 
