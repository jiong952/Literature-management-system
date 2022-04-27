#include "includes.h"

//遍历B树
void Traverse(BTree t, int k) {
	if (t != NULL) {
		int i;
		for (i = 1;i <= t->keynum;i++) {
			//非终端结点
			if (t->ptr[i - 1] != NULL) {  
				if (i == 1) {
					for (int j = 1;j <= (k * 2);j++) printf("  ");
					for (int j = 1;j <= t->keynum;j++) {
						if (j == t->keynum) printf("%d\n", t->key[j]);
						else printf("%d,", t->key[j]);
					}
					k++;
				}
			}
			//终端结点
			else {                       
				if (i == 1 && i == t->keynum) {
					for (int j = 1;j <= (k * 2);j++) printf("  ");
					printf("%d\n", t->key[i]);
				}
				if (i == 1 && i < t->keynum) {
					for (int j = 1;j <= (k * 2);j++) printf("  ");
					printf("%d,", t->key[i]);
				}
				if (i != 1 && i < t->keynum) {
					printf("%d,", t->key[i]);
				}
				if (i != 1 && i == t->keynum) {
					printf("%d\n", t->key[i]);
				}
			}
			if (i == 1)
				Traverse(t->ptr[i - 1], k);
			Traverse(t->ptr[i], k);  
		}
	}
}

//凹入表输出
void PrintBTree(BTree t) {
	printf("当前B树的状态如下：\n");
	if (t == NULL)
		printf("此B树为空树\n");
	else
		Traverse(t, 0); 
}

