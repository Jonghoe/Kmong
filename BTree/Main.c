#include "BTree.h"   
#include <stdio.h>
#include<stdlib.h>

void printMenu() {
	printf("\n---�޴�---\n");
	printf(" 0. ����\n");
	printf(" 1. ����\n");
	printf(" 2. ����\n");
	printf(" 3. ���\n");
	printf("----------\n");
	printf(" >> ");
}
int main(void)
{
	int menu = 0;
	int input = 0;
	int temp = 0;
	BTree* Tree;
	Make_BTree(&Tree);
	while (1) {
		fflush(stdin);
		printMenu();
		scanf_s("%d", &menu);		switch (menu) {
		case 0:
			printf(" ���α׷��� �����մϴ�.\n");
			return 1;
		case 1:
			printf(" Insert key >>");
			scanf_s("%d", &input);
			Insert(Tree, input);
			printf(" \t%d ���ԵǾ����ϴ�.\n",input);
			break;
		case 2:
			printf(" Remove key >> ");
			scanf_s("%d", &input);
			if (Delete(Tree, &input)){
				printf(" \t%d �����Ǿ����ϴ�.\n", input);
			}
			else
				printf("\t%d �� ���� ���� �ʽ��ϴ�.\n", input);
			
			break;
		case 3:
			printf("��ü ��� ���� : ");
			inoder(Tree);
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n");
			break;
		}
	}
	free(Tree);
}