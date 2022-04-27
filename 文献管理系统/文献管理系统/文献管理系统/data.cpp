#include "includes.h"


//日志记录 
void log_reocrd(int error_level, const char *format, ...)
{
	
    va_list args;
    FILE *fp=NULL;
    char time_str[32];
    char file_name[256];
 
    va_start (args, format);
    time_t time_log = time(NULL);
    strftime(file_name,sizeof(file_name),"%Y-%m-%d_log_history.log",localtime(&time_log));
 
    if((fp=fopen(file_name,"a+"))!=NULL)
    {
        strftime(time_str,sizeof(time_str),"%Y-%m-%d %H:%M:%S",localtime(&time_log));
        if(error_level==(int)Error)
        {
            fprintf (fp, "[%s]-[%s]-[%s]-[%d] :> ",time_str,"ERROR",__FILE__,__LINE__);
            vfprintf (fp,format,args);
            fprintf (fp,"\n");
 
        }
        else if(error_level==(int)Waring)
        {
            fprintf (fp, "[%s]-[%s]-[%s]-[%d] :> ",time_str,"WARNINGs",__FILE__,__LINE__);
            vfprintf (fp,format,args);
            fprintf (fp,"\n");
        }
        else if(error_level==(int)Info)
        {
            fprintf (fp, "[%s]-[%s]-[%s]-[%d] :> ",time_str,"INFO",__FILE__,__LINE__);
            vfprintf (fp,format,args);
            fprintf (fp,"\n");
        }
        else if(error_level==(int)Debug)
        {
            fprintf (fp, "[%s]-[%s]-[%s]-[%d] :> ",time_str,"DEBUG",__FILE__,__LINE__);
            vfprintf (fp,format,args);
            fprintf (fp,"\n");
        }
        fclose(fp);
    }
 
    va_end (args);
}

//从文件中读取书本数据 
void Init(BTree &t){
    FILE *r;
    r= fopen("BookData.txt","r");
    if(r==NULL){
     printf("打开文件失败!");
     exit(0) ;
 }
    BookType* book = (BookType *)malloc(sizeof(BookType));
    book->borrower = NULL;
    book->booker = NULL;
    int key = 0;
    while(fscanf(r,"%d %s %s %s %d %d",&key,book->bookName,book->writerName,book->bookPress,&book->booknumAll,&book->booknumNow)!=EOF)
    {   
        InsertBTree(t,key,book);
		book = (BookType *)malloc(sizeof(BookType));
    	book->borrower = NULL;
    	book->booker = NULL;
    }
    free(book);
    book=NULL;
    fclose(r);
} 



void Save(BTree &T){
	FILE* fp = NULL;
	if((fp = fopen("BookData.txt", "w")) == NULL){
		printf("无法打开文件!\n");
		return;
	}
	save_btree(T, fp);
	fclose(fp);
	return;
}

void save_btree(BTree &T, FILE* fp){	
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keynum; i++){
		save_btree(T->ptr[i], fp);
		fprintf(fp, "%d %s %s %s %d %d\n", T->key[i+1], 
			T->books[i+1]->bookName,
			T->books[i+1]->writerName,
			T->books[i+1]->bookPress,
			T->books[i+1]->booknumNow, 
			T->books[i+1]->booknumAll);
	}
	save_btree(T->ptr[i], fp);
	return;
}

