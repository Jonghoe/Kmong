#include "sort.h"

void InsertionSort(int list[], int n) {
	int i, j,k;
	for (i = 1; i < n; i++){
		//i��° list �� �� ���� ���ڵ��� ���Ͽ� �´� �ڸ���
		//���� ���� ����
		for (j = i - 1; j >= 0 && list[i]<list[j]; j--);
	
		if (j != i - 1)
			for (k = i; k > j + 1; k--)
				Swap(list, k, k - 1);

	}
}
