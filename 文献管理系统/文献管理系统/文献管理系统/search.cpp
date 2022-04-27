#include "includes.h"

void SearchBTree(BTree t, int k, result &r){
    int i = 0, found = 0;
    //��m��B��t�ϲ�������k����r����(pt,i,tag)
    //������ҳɹ�������tag=1��ָ��pt��ָ����е�i����������k
    //����tag=0����Ҫ��������Ϊk�ļ�¼��Ӧλ��pt����е�i-1���͵�i������֮��
    BTree p = t, q = NULL;
    while(p!=NULL&&0==found){
        i = Search(p, k); //��p->key[1..p->keynum]�в���p->key[i-1]<k<=p->key[i]
        if(i<=p->keynum && p->key[i]==k) found = 1; //�ҵ���������
        else{
            q = p;
            p = p->ptr[i-1];
        }//ָ������
    }
    if(1 == found){//���ҳɹ�������k��λ��p��i
        r.node = p; r.index = i; r.tag = 1;
    }else{  //���Ҳ��ɹ�������k�Ĳ���λ��q��i
        r.node = q; r.index = i; r.tag = 0;
    }
    return;
}
//��p->key[1..p->keynum]�в���p->key[i-1]<k<=p->key[i]
int Search(BTree p, int k){ //��p->key[1..p->keynum]��k
    int i=1;
    while(i <= p->keynum&&k>p->key[i]) i++;
    return i;
}
