#include "includes.h"

//创建
void InitBTree(BTree &t) {
    BookType* books[18];
    KeyType key[] = { 35,14,17,71,3,54,21,62,13,16,12,45,27,42,10,90,88,7 };
    int num[] = { 1,6,41,87,5,12,40,51,64,73,5,40,47,50,59,98,87,85 };
    char name[18][30] = { "数据结构","简明大学物理学","大学物理学（上册）","大学物理实验","电路（第5版）","电工与电子技术实验教程","C语言程序设计",
        "复变函数（第二版）","半导体物理","概率论与数理统计","专业实验基础","离散数学及其应用","高等数学（上册）","高等数学（下册）",
        "计算机科学概论","线性代数","电工学（上册）","电工学（下册）" };
    char writer[18][40] = { "吴伟民","范仰才","范仰才","朱道云","邱关源","彭端","王绵森","刘恩科","旭里","微电子系",
        "朱平","傅彦","同济大学数学系","同济大学数学系","张爱红","同济大学数学系","苏林","刘成悦" };
    char press[18][40] = { "高等教育出版社","高等教育出版社","北京大学出版社","北京大学出版社","高等教育出版社",
        "吉林大学出版社","高等教育出版社","电子工业出版社","化学工业出版社","广东工业大学出版社","广西师范大学出版社",
        "高等教育出版社","高等教育出版社","高等教育出版社","人民邮电出版社","高等教育出版社","复旦大学出版社","复旦大学出版社" };
    int j,n=18;
	for (j = 0;j < n;j++) {     //逐一插入元素
        books[j] = (BookType *)malloc(sizeof(BookType));
        strcpy(books[j]->bookName,name[j]);
        strcpy(books[j]->writerName, writer[j]);
        strcpy(books[j]->bookPress, press[j]);
        books[j]->booknumAll = num[j];
        books[j]->booknumNow = num[j];
        books[j]->borrower = NULL;
        books[j]->booker = NULL;
        InsertBTree(t,key[j],books[j]);
    }
}

void InitBTNode(BTree &p){
    p = (BTree)malloc(sizeof(BTNode));
    //对p的子节点初始化
    for(int i = 0;i<=m+1;i++){
        p->key[i] = -1;
        p->ptr[i] = NULL;
        // p->books[i].bookName = NULL;
    }
    p->keynum = 0;
    p->parent = NULL;
    return;
}

int InsertBTree(BTree &T, int k, BookType* book){
    result result;
    //查找是否已经存在
    SearchBTree(T, k, result);
    if(result.tag) return 0; //已存在则不执行插入
    Insert(result.node, k, result.index, NULL, book);
    BTree ap;
    while (result.node->keynum >= MAX_NUM  ){
		split(result.node, ap);
        k=result.node->key[SPLIT_INDEX]; 
		if (result.node->parent == NULL){
            //最顶层
            newRoot(T, result.node, ap, k, result.node->books[SPLIT_INDEX]);
            k = -1;
        }
		else {
			int index = Search(result.node->parent, k); //在双亲结点中查找k的插入位置
			Insert(result.node->parent, k, index, ap, result.node->books[SPLIT_INDEX]);
		}
        result.node = result.node->parent; //上移一层
        if(result.node==NULL) break;
    }
    return 1;
}

void split(BTree &q, BTree &ap){
    //将q结点分裂成两个结点，前一半保留在原节点，另一半移入ap所指向的新节点
    int i, j, n = q->keynum;
    ap = (BTNode*)malloc(sizeof(BTNode));   //生成新结点
    InitBTNode(ap);
    ap->ptr[0] = q->ptr[SPLIT_INDEX];
    for(i = SPLIT_INDEX + 1, j = 1; i<=n;i++,j++){  //后一半移入ap结点
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
        ap->books[j] = q->books[i];
        q->key[i] = -1;
        q->ptr[i] = NULL;
    }
    ap->keynum = n-SPLIT_INDEX;
    ap->parent = q->parent;
    for(i=0;i<=n-SPLIT_INDEX;i++)   //修改新结点的子节点的parent域
        if(ap->ptr[i]!=NULL) ap->ptr[i]->parent = ap;
    q->keynum = SPLIT_INDEX - 1;    //q的前一半保留，修改keynum
    return;
}

void newRoot(BTree &t, BTree p, BTree ap, int k, BookType* book){      //生成新的根节点 p是左子树 ap是右子树
    t = (BTNode*)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = k;
    t->books[1] = book;
    if(p!=NULL) p->parent = t;
    if(ap!=NULL) ap->parent = t;
    t->parent = NULL;   //新根的双亲是空指针
}

void Insert(BTree &q, int k, int index, BTree ap, BookType* book){
    //关键字k和新结点指针ap分别插入到q->key[i]和q->ptr[i]
    int i;
    //将待插入结点后的所有结点后移
    for(i = q->keynum; i>=index; i--){
        q->key[i+1] = q->key[i];
        q->ptr[i+1] = q->ptr[i];
        q->books[i+1] = q->books[i];
    }
    q->key[index] = k;
    q->ptr[index] = ap;
    q->books[index] = book;
    if(ap!=NULL) ap->parent = q;
    q->keynum++;
    return;
}



