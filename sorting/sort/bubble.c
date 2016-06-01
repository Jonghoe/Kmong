#include "sort.h"

void BubbleSort(int list[], int n) {
	int i = 0;
	int j;
	// 큰 값부터 시작하여 자리 정렬 비교해가며 값이 큰놈이 뒤로 가게끔 스왑
	for(; i < n ; i++) 
		for (j = 1; j < n - i ; j++) 
			if (list[j - 1] > list[j]) 
				Swap(list, j - 1, j);
}
