#include "includes.h"

int DeleteBTree(BTree &T, int key){
	//删除索引为key的记录
	result r;
    SearchBTree(T, key, r);
	if (r.tag == 0) return 0;
	//若不是终端结点，将直接前驱的索引和值覆盖掉当前结点
	if (r.node->ptr[0] != NULL) Successor(r.node, r.index);
	//更新key的值为前驱结点
	key = r.node->key[r.index];
	//从结点p中删除key[i]
	Remove(r.node, r.index);
	//找到
	int index = Search(r.node->parent, key) - 1;
	//调整树
	if (r.node->parent != NULL && r.node->keynum < MIN_NUM)
        Restore(r.node, index);
	return 1;
}

//若不是终端结点，将直接前驱的索引和值覆盖掉当前结点
void Successor(BTree &node, int &index){
    if(node == NULL) return;
	//寻找直接前驱
	if(node->ptr[index - 1] == NULL) return;
	BTree p = node->ptr[index - 1];
	while(p->ptr[p->keynum] != NULL)
        p = p->ptr[p->keynum];
	//将直接前驱的索引和值覆盖掉当前结点
	node->key[index] = p->key[p->keynum];
	node->books[index] = p->books[p->keynum];
	//令node指向待删除的直接前驱结点
	node = p;
	index = p->keynum;
}

//从结点p中删除key[i]
int Remove(BTree& node, int i){
	if (node == NULL) return 0;
	//将删除结点后结点前移
	for (; i < node->keynum; i++) {
		node->key[i] = node->key[i+1];
		node->books[i] = node->books[i+1];
	}
	node->keynum--;
	return 1;
}

//向父结点插入关键字
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

//调整树
void Restore(BTree& node, int index) {
	BTree parent,l_brother, r_brother;
	parent = node->parent;
	//左兄弟够借
	if (index > 0 && (l_brother = parent->ptr[index - 1])->keynum > MIN_NUM) {
		//该节点插入直接前驱
		Insert(node, parent->key[index], 1, node->ptr[0], parent->books[index]);
		//改变孩子指针
		node->ptr[0] = l_brother->ptr[l_brother->keynum];
		if (l_brother->ptr[l_brother->keynum] != NULL) l_brother->ptr[l_brother->keynum]->parent = node;
		//移除父节点中其直接前驱
		Remove(parent, index);
		//将直接前驱的直接前驱插入到父节点
		InsertBookType(parent, l_brother->key[l_brother->keynum], index, l_brother->books[l_brother->keynum]);
		//将直接前驱的直接前驱删除
		Remove(l_brother, l_brother->keynum);
	}
	//左兄弟不够，右兄弟够借
	else if (index < parent->keynum && (r_brother = parent->ptr[index + 1])->keynum > MIN_NUM) {
		Insert(node, parent->key[index+1], node->keynum + 1, r_brother->ptr[0], parent->books[index + 1]);
		Remove(parent, index + 1);
		InsertBookType(parent, r_brother->key[1], index + 1, r_brother->books[1]);
		Remove(r_brother, 1);
		for (int i=0; i <= r_brother->keynum; i++) r_brother->ptr[i] = r_brother->ptr[i + 1];
	}
	//兄弟不够借，合并左子树
	else if (index > 0) {
		l_brother = parent->ptr[index - 1];
		Insert(node, parent->key[index], 1, node->ptr[0], parent->books[index]);
		Remove(parent, index);
		CombineBTNode(l_brother, node);
		node = l_brother;
		for (int i = index; i <= parent->keynum; i++) parent->ptr[i] = parent->ptr[i + 1];
		//调整父节点至平衡
		if (parent->keynum < MIN_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else Restore(parent, Search(parent->parent, node->key[1]) - 1);
		}
	}
	//兄弟不够借，合并右子树
	else {
		r_brother = parent->ptr[index + 1];
		Insert(node, parent->key[index+1],node->keynum + 1, r_brother->ptr[0], parent->books[index + 1]);
		Remove(parent, index + 1);
		CombineBTNode(node, r_brother);
		for (int i = index + 1; i <= parent->keynum; i++) 
            parent->ptr[i] = parent->ptr[i + 1];
		//调整父节点至平衡
		if (parent->keynum < MIN_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else Restore(parent, Search(parent->parent, node->key[node->keynum + 1]) - 1);
		}
	}
}

//合并结点
void CombineBTNode(BTree& l_node, BTree& r_node) {
	//左结点为空返回
	if (l_node == NULL) return;
	//将右结点所有记录合并到左结点
	for (int i = 1; i <= r_node->keynum; i++) {
		Insert(l_node, r_node->key[i], l_node->keynum + 1, r_node->ptr[i], r_node->books[i]);
	}
	//释放右节点
	free(r_node);
    return;
}

//将合并后结点中所有记录插入到父节点中
void DeleteRoot(BTree& root) {
	BTree node = root->ptr[0];
	//父节点指向node的孩子
	root->ptr[0] = node->ptr[0];
	//非终端结点，孩子结点指向父节点
	if (node->ptr[0] != NULL) node->ptr[0]->parent = root;
	//将所有记录插入到父节点
	for (int i = 1; i <= node->keynum; i++) Insert(root, node->key[i], i, node->ptr[i], node->books[i]);
	//释放该节点
	free(node);
    return;
}

