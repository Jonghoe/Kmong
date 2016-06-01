#include "sort.h"
#include <stdlib.h>

void QuickSort(int list[], int n) {
	int begin = 0, end = n,Val=0;
	int k,i, j,Top=-1,Swap_I;
	int* Stack = (int*)malloc(n*sizeof(int));
	int* Check = (int*)malloc(n*sizeof(int));
	// Check ���� ���������� ��Ÿ��
	for (k = 0; k < n; k++)
		Check[k] = 0;
	Stack[++Top] = n-1;
	Stack[++Top] = 0;
	//���� �� ���� ���� n�� �� �� ����
	while (Val != n){
		Val = 0;
		// ���۰� ���� ������ �� �ڸ��� ����
		do{
			begin = Stack[Top--];
			i = begin + 1;
			end = Stack[Top--];
			j = end ;
			if (begin == end)
				Check[begin] = 1;
		} while (begin >= end && Top > -1);
		//���� �ڸ� ������ �� �Ȱ�� �ݺ����� ���� ���´�
		for (k = 0; k < n; k++)
			if (Check[k] == 1)Val++;
		if (Val == n)
			break;

		while (i<j){
			// �� �κ� ���� ū ���� ã�� �ݺ���
			for (; i < j&& list[begin] >= list[i]; i++);
			// i , j �� ���� �ϸ� ���� ���� begin ��ġ�� ����
			if (i >= j)break;
			// �� �κ� ���� ���� ���� ã�� �ݺ���
			for (; j > i && list[begin] <= list[j]; j--);
			Swap(list, i, j);
		}
		
		// ���� �� ������ ���� ���� ���۰��� �ڸ� ��ȯ �� �� �� ����
		Swap_I = list[i - 1] <= list[i] ? i - 1 : i;
		Swap(list, begin, Swap_I);
		Check[Swap_I] = 1;
		
		// �ڸ� �ٲ� �� begin ~ �����ڸ� �� / �����ڸ� �� ~ end �α������� ������ �ٽ� sorting
		Stack[++Top] = end;
		Stack[++Top] = Swap_I + 1;
		Stack[++Top] = Swap_I - 1;
		Stack[++Top] = begin;
		
		
	}
	free(Stack);
	free(Check);
}
