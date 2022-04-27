#include "includes.h"

//����B��
void Traverse(BTree t, int k) {
	if (t != NULL) {
		int i;
		for (i = 1;i <= t->keynum;i++) {
			//���ն˽��
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
			//�ն˽��
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

//��������
void PrintBTree(BTree t) {
	printf("��ǰB����״̬���£�\n");
	if (t == NULL)
		printf("��B��Ϊ����\n");
	else
		Traverse(t, 0); 
}

