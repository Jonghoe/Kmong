#include "sort.h"
#include <stdlib.h>

void Merge(int list[],int Tmp[], int left,int mid,int right){
	int i, l = left;
	int m = mid + 1, n = right - left;
	//비교하여 작은 값을 집어 넣음
	for ( i = 0; l <= mid&&m <= right; i++)
		Tmp[i] = list[l] < list[m] ? list[l++] : list[m++];

	// 남아있는걸 다 넣는 과정
	if (l == mid+1)
		for (; m <= right; m++,i++)
			Tmp[i] = list[m];
	else
		for (; l <= mid; l++,i++)
			Tmp[i] = list[l];
	//임시 저장 공간에서 원래 리스트로 저장
	for (i = 0; i <= right - left; i++)
		list[i + left] = Tmp[i];
}
void MergeSorting(int list[],int ar[], int left, int right){
	//반씩 나누면서 재귀호출을 이용하여 합병해 나감
	int mid;
	if (left < right){
		mid = (left + right) / 2;
		MergeSorting(list,ar, left, mid);
		MergeSorting(list,ar, mid+1, right);
		Merge(list, ar, left, mid, right);
	}
}
void MergeSort(int list[], int n) {
	int * Tmp = (int*)malloc(sizeof(int)*n);
	MergeSorting(list,Tmp, 0, n-1);
	free(Tmp);
}
