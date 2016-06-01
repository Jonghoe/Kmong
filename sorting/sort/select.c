#include "sort.h"

void SelectSort(int list[], int n) {
	int i,j,min,min_L;
	for (i = 0; i < n; i++) {
		// 최초의 값을 가장 작은 값으로 설정 위치도 마찬가지
		min = list[i];
		min_L = i;
		// 가장 작은값을 찾기 위한 반복문
		for(j = i; j < n; j++) 
			if (min > list[j]){
				min = list[j];
				min_L = j;
			}
		// 가장 작은 값과 위치 바꿈
		Swap(list, i, min_L);
    }
 }
