#include "BTree.h"   
#include <stdio.h>
#include<stdlib.h>

void printMenu() {
	printf("\n---메뉴---\n");
	printf(" 0. 종료\n");
	printf(" 1. 삽입\n");
	printf(" 2. 삭제\n");
	printf(" 3. 출력\n");
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
			printf(" 프로그램을 종료합니다.\n");
			return 1;
		case 1:
			printf(" Insert key >>");
			scanf_s("%d", &input);
			Insert(Tree, input);
			printf(" \t%d 삽입되었습니다.\n",input);
			break;
		case 2:
			printf(" Remove key >> ");
			scanf_s("%d", &input);
			if (Delete(Tree, &input)){
				printf(" \t%d 삭제되었습니다.\n", input);
			}
			else
				printf("\t%d 가 존재 하지 않습니다.\n", input);
			
			break;
		case 3:
			printf("전체 노드 보기 : ");
			inoder(Tree);
			break;
		default:
			printf("잘못된 입력입니다.\n");
			break;
		}
	}
	free(Tree);
}