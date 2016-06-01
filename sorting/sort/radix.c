#include "sort.h"
#include <stdlib.h>

void RadixSort(int list[], int n) {
	int i, j,k,_i=0;
	int Max_L = 1, Max = list[0];
	int*Tmp[10];
	//Radix 값들을 저장할 공간 생성
	for (i = 0; i < 10; i++){
		Tmp[i] = (int*)malloc(sizeof(int)*n);
		for (j = 0; j < n; j++)
			Tmp[i][j] = -1;
	}
	//가장 큰 값을 찾아서 그 값의 길이를 구함
	for (i = 0; i < n; i++)
		if (Max < list[i])
			Max = list[i];
	for (i = 1; (Max / i) > 10; i *= 10)Max_L++;

	//가장 작은 자리 수 부터 가장 큰 자리 수 까지 정렬
	for (i = 1; i <= Max_L; i++){
		_i = 0;
		for (j = 0; j < n; j++){
			int index = (list[j] % (i * 10)) / i;
			for (k = 0; k < n&&Tmp[index][k] != -1; k++);
			Tmp[index][k] = list[j];
		}
		for (j = 0; j < 10; j++)
			for (k = 0; k < n&&Tmp[j][k] != -1; k++){
				list[_i++] = Tmp[j][k];
				Tmp[j][k] = -1;
			}
	}

	for (i = 0; i < 10; i++)
		free(Tmp[i]);
	
}
