#include "sort.h"

void BubbleSort(int list[], int n) {
	int i = 0;
	int j;
	// ū ������ �����Ͽ� �ڸ� ���� ���ذ��� ���� ū���� �ڷ� ���Բ� ����
	for(; i < n ; i++) 
		for (j = 1; j < n - i ; j++) 
			if (list[j - 1] > list[j]) 
				Swap(list, j - 1, j);
}
