#include "includes.h"

//����
void InitBTree(BTree &t) {
    BookType* books[18];
    KeyType key[] = { 35,14,17,71,3,54,21,62,13,16,12,45,27,42,10,90,88,7 };
    int num[] = { 1,6,41,87,5,12,40,51,64,73,5,40,47,50,59,98,87,85 };
    char name[18][30] = { "���ݽṹ","������ѧ����ѧ","��ѧ����ѧ���ϲᣩ","��ѧ����ʵ��","��·����5�棩","�繤����Ӽ���ʵ��̳�","C���Գ������",
        "���亯�����ڶ��棩","�뵼������","������������ͳ��","רҵʵ�����","��ɢ��ѧ����Ӧ��","�ߵ���ѧ���ϲᣩ","�ߵ���ѧ���²ᣩ",
        "�������ѧ����","���Դ���","�繤ѧ���ϲᣩ","�繤ѧ���²ᣩ" };
    char writer[18][40] = { "��ΰ��","������","������","�����","���Դ","���","����ɭ","������","����","΢����ϵ",
        "��ƽ","����","ͬ�ô�ѧ��ѧϵ","ͬ�ô�ѧ��ѧϵ","�Ű���","ͬ�ô�ѧ��ѧϵ","����","������" };
    char press[18][40] = { "�ߵȽ���������","�ߵȽ���������","������ѧ������","������ѧ������","�ߵȽ���������",
        "���ִ�ѧ������","�ߵȽ���������","���ӹ�ҵ������","��ѧ��ҵ������","�㶫��ҵ��ѧ������","����ʦ����ѧ������",
        "�ߵȽ���������","�ߵȽ���������","�ߵȽ���������","�����ʵ������","�ߵȽ���������","������ѧ������","������ѧ������" };
    int j,n=18;
	for (j = 0;j < n;j++) {     //��һ����Ԫ��
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
    //��p���ӽڵ��ʼ��
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
    //�����Ƿ��Ѿ�����
    SearchBTree(T, k, result);
    if(result.tag) return 0; //�Ѵ�����ִ�в���
    Insert(result.node, k, result.index, NULL, book);
    BTree ap;
    while (result.node->keynum >= MAX_NUM  ){
		split(result.node, ap);
        k=result.node->key[SPLIT_INDEX]; 
		if (result.node->parent == NULL){
            //���
            newRoot(T, result.node, ap, k, result.node->books[SPLIT_INDEX]);
            k = -1;
        }
		else {
			int index = Search(result.node->parent, k); //��˫�׽���в���k�Ĳ���λ��
			Insert(result.node->parent, k, index, ap, result.node->books[SPLIT_INDEX]);
		}
        result.node = result.node->parent; //����һ��
        if(result.node==NULL) break;
    }
    return 1;
}

void split(BTree &q, BTree &ap){
    //��q�����ѳ�������㣬ǰһ�뱣����ԭ�ڵ㣬��һ������ap��ָ����½ڵ�
    int i, j, n = q->keynum;
    ap = (BTNode*)malloc(sizeof(BTNode));   //�����½��
    InitBTNode(ap);
    ap->ptr[0] = q->ptr[SPLIT_INDEX];
    for(i = SPLIT_INDEX + 1, j = 1; i<=n;i++,j++){  //��һ������ap���
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
        ap->books[j] = q->books[i];
        q->key[i] = -1;
        q->ptr[i] = NULL;
    }
    ap->keynum = n-SPLIT_INDEX;
    ap->parent = q->parent;
    for(i=0;i<=n-SPLIT_INDEX;i++)   //�޸��½����ӽڵ��parent��
        if(ap->ptr[i]!=NULL) ap->ptr[i]->parent = ap;
    q->keynum = SPLIT_INDEX - 1;    //q��ǰһ�뱣�����޸�keynum
    return;
}

void newRoot(BTree &t, BTree p, BTree ap, int k, BookType* book){      //�����µĸ��ڵ� p�������� ap��������
    t = (BTNode*)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = k;
    t->books[1] = book;
    if(p!=NULL) p->parent = t;
    if(ap!=NULL) ap->parent = t;
    t->parent = NULL;   //�¸���˫���ǿ�ָ��
}

void Insert(BTree &q, int k, int index, BTree ap, BookType* book){
    //�ؼ���k���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
    int i;
    //���������������н�����
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



