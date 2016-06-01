#include "sort.h"

void InsertionSort(int list[], int n) {
	int i, j,k;
	for (i = 1; i < n; i++){
		//i번째 list 와 그 전의 숫자들을 비교하여 맞는 자리에
		//값을 집어 넣음
		for (j = i - 1; j >= 0 && list[i]<list[j]; j--);
	
		if (j != i - 1)
			for (k = i; k > j + 1; k--)
				Swap(list, k, k - 1);

	}
}
