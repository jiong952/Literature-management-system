#include "includes.h"

int DeleteBTree(BTree &T, int key){
	//ɾ������Ϊkey�ļ�¼
	result r;
    SearchBTree(T, key, r);
	if (r.tag == 0) return 0;
	//�������ն˽�㣬��ֱ��ǰ����������ֵ���ǵ���ǰ���
	if (r.node->ptr[0] != NULL) Successor(r.node, r.index);
	//����key��ֵΪǰ�����
	key = r.node->key[r.index];
	//�ӽ��p��ɾ��key[i]
	Remove(r.node, r.index);
	//�ҵ�
	int index = Search(r.node->parent, key) - 1;
	//������
	if (r.node->parent != NULL && r.node->keynum < MIN_NUM)
        Restore(r.node, index);
	return 1;
}

//�������ն˽�㣬��ֱ��ǰ����������ֵ���ǵ���ǰ���
void Successor(BTree &node, int &index){
    if(node == NULL) return;
	//Ѱ��ֱ��ǰ��
	if(node->ptr[index - 1] == NULL) return;
	BTree p = node->ptr[index - 1];
	while(p->ptr[p->keynum] != NULL)
        p = p->ptr[p->keynum];
	//��ֱ��ǰ����������ֵ���ǵ���ǰ���
	node->key[index] = p->key[p->keynum];
	node->books[index] = p->books[p->keynum];
	//��nodeָ���ɾ����ֱ��ǰ�����
	node = p;
	index = p->keynum;
}

//�ӽ��p��ɾ��key[i]
int Remove(BTree& node, int i){
	if (node == NULL) return 0;
	//��ɾ��������ǰ��
	for (; i < node->keynum; i++) {
		node->key[i] = node->key[i+1];
		node->books[i] = node->books[i+1];
	}
	node->keynum--;
	return 1;
}

//�򸸽�����ؼ���
int InsertBookType(BTree& node, int key,int i, BookType* book) {
	if (node == NULL) return 0;
	for (int j = node->keynum; j >= i; j--) {
		node->key[j + 1] = node->key[j];
		node->books[j + 1] = node->books[j];
	}
	node->key[i] = key;
	node->books[i] = book;
	node->keynum++;
    return 1;
}

//������
void Restore(BTree& node, int index) {
	BTree parent,l_brother, r_brother;
	parent = node->parent;
	//���ֵܹ���
	if (index > 0 && (l_brother = parent->ptr[index - 1])->keynum > MIN_NUM) {
		//�ýڵ����ֱ��ǰ��
		Insert(node, parent->key[index], 1, node->ptr[0], parent->books[index]);
		//�ı亢��ָ��
		node->ptr[0] = l_brother->ptr[l_brother->keynum];
		if (l_brother->ptr[l_brother->keynum] != NULL) l_brother->ptr[l_brother->keynum]->parent = node;
		//�Ƴ����ڵ�����ֱ��ǰ��
		Remove(parent, index);
		//��ֱ��ǰ����ֱ��ǰ�����뵽���ڵ�
		InsertBookType(parent, l_brother->key[l_brother->keynum], index, l_brother->books[l_brother->keynum]);
		//��ֱ��ǰ����ֱ��ǰ��ɾ��
		Remove(l_brother, l_brother->keynum);
	}
	//���ֵܲ��������ֵܹ���
	else if (index < parent->keynum && (r_brother = parent->ptr[index + 1])->keynum > MIN_NUM) {
		Insert(node, parent->key[index+1], node->keynum + 1, r_brother->ptr[0], parent->books[index + 1]);
		Remove(parent, index + 1);
		InsertBookType(parent, r_brother->key[1], index + 1, r_brother->books[1]);
		Remove(r_brother, 1);
		for (int i=0; i <= r_brother->keynum; i++) r_brother->ptr[i] = r_brother->ptr[i + 1];
	}
	//�ֵܲ����裬�ϲ�������
	else if (index > 0) {
		l_brother = parent->ptr[index - 1];
		Insert(node, parent->key[index], 1, node->ptr[0], parent->books[index]);
		Remove(parent, index);
		CombineBTNode(l_brother, node);
		node = l_brother;
		for (int i = index; i <= parent->keynum; i++) parent->ptr[i] = parent->ptr[i + 1];
		//�������ڵ���ƽ��
		if (parent->keynum < MIN_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else Restore(parent, Search(parent->parent, node->key[1]) - 1);
		}
	}
	//�ֵܲ����裬�ϲ�������
	else {
		r_brother = parent->ptr[index + 1];
		Insert(node, parent->key[index+1],node->keynum + 1, r_brother->ptr[0], parent->books[index + 1]);
		Remove(parent, index + 1);
		CombineBTNode(node, r_brother);
		for (int i = index + 1; i <= parent->keynum; i++) 
            parent->ptr[i] = parent->ptr[i + 1];
		//�������ڵ���ƽ��
		if (parent->keynum < MIN_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else Restore(parent, Search(parent->parent, node->key[node->keynum + 1]) - 1);
		}
	}
}

//�ϲ����
void CombineBTNode(BTree& l_node, BTree& r_node) {
	//����Ϊ�շ���
	if (l_node == NULL) return;
	//���ҽ�����м�¼�ϲ�������
	for (int i = 1; i <= r_node->keynum; i++) {
		Insert(l_node, r_node->key[i], l_node->keynum + 1, r_node->ptr[i], r_node->books[i]);
	}
	//�ͷ��ҽڵ�
	free(r_node);
    return;
}

//���ϲ����������м�¼���뵽���ڵ���
void DeleteRoot(BTree& root) {
	BTree node = root->ptr[0];
	//���ڵ�ָ��node�ĺ���
	root->ptr[0] = node->ptr[0];
	//���ն˽�㣬���ӽ��ָ�򸸽ڵ�
	if (node->ptr[0] != NULL) node->ptr[0]->parent = root;
	//�����м�¼���뵽���ڵ�
	for (int i = 1; i <= node->keynum; i++) Insert(root, node->key[i], i, node->ptr[i], node->books[i]);
	//�ͷŸýڵ�
	free(node);
    return;
}

