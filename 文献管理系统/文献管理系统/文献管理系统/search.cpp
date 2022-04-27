#include "includes.h"

void SearchBTree(BTree t, int k, result &r){
    int i = 0, found = 0;
    //在m阶B树t上查找索引k，用r返回(pt,i,tag)
    //如果查找成功，则标记tag=1，指针pt所指结点中第i个索引等于k
    //否则tag=0，若要插入索引为k的记录，应位于pt结点中第i-1个和第i个索引之间
    BTree p = t, q = NULL;
    while(p!=NULL&&0==found){
        i = Search(p, k); //在p->key[1..p->keynum]中查找p->key[i-1]<k<=p->key[i]
        if(i<=p->keynum && p->key[i]==k) found = 1; //找到待查索引
        else{
            q = p;
            p = p->ptr[i-1];
        }//指针下移
    }
    if(1 == found){//查找成功，返回k的位置p及i
        r.node = p; r.index = i; r.tag = 1;
    }else{  //查找不成功，返回k的插入位置q及i
        r.node = q; r.index = i; r.tag = 0;
    }
    return;
}
//在p->key[1..p->keynum]中查找p->key[i-1]<k<=p->key[i]
int Search(BTree p, int k){ //在p->key[1..p->keynum]找k
    int i=1;
    while(i <= p->keynum&&k>p->key[i]) i++;
    return i;
}
