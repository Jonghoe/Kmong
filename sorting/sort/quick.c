#include "sort.h"
#include <stdlib.h>

void QuickSort(int list[], int n) {
	int begin = 0, end = n,Val=0;
	int k,i, j,Top=-1,Swap_I;
	int* Stack = (int*)malloc(n*sizeof(int));
	int* Check = (int*)malloc(n*sizeof(int));
	// Check 값이 고정됬음을 나타냄
	for (k = 0; k < n; k++)
		Check[k] = 0;
	Stack[++Top] = n-1;
	Stack[++Top] = 0;
	//고정 된 값의 수가 n개 일 때 까지
	while (Val != n){
		Val = 0;
		// 시작과 끝이 같으면 그 자리에 고정
		do{
			begin = Stack[Top--];
			i = begin + 1;
			end = Stack[Top--];
			j = end ;
			if (begin == end)
				Check[begin] = 1;
		} while (begin >= end && Top > -1);
		//만약 자리 고정이 다 된경우 반복문을 빠져 나온다
		for (k = 0; k < n; k++)
			if (Check[k] == 1)Val++;
		if (Val == n)
			break;

		while (i<j){
			// 앞 부분 보다 큰 값을 찾는 반복문
			for (; i < j&& list[begin] >= list[i]; i++);
			// i , j 가 교차 하면 작은 값을 begin 위치와 스왑
			if (i >= j)break;
			// 뒷 부분 보다 작은 값을 찾는 반복문
			for (; j > i && list[begin] <= list[j]; j--);
			Swap(list, i, j);
		}
		
		// 남은 두 숫자중 작은 값을 시작값과 자리 변환 후 그 값 고정
		Swap_I = list[i - 1] <= list[i] ? i - 1 : i;
		Swap(list, begin, Swap_I);
		Check[Swap_I] = 1;
		
		// 자리 바꾼 후 begin ~ 고정자리 좌 / 고정자리 우 ~ end 두구역으로 나눠서 다시 sorting
		Stack[++Top] = end;
		Stack[++Top] = Swap_I + 1;
		Stack[++Top] = Swap_I - 1;
		Stack[++Top] = begin;
		
		
	}
	free(Stack);
	free(Check);
}
