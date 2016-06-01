#include "sort.h"
#include <stdlib.h>

void Merge(int list[],int Tmp[], int left,int mid,int right){
	int i, l = left;
	int m = mid + 1, n = right - left;
	//���Ͽ� ���� ���� ���� ����
	for ( i = 0; l <= mid&&m <= right; i++)
		Tmp[i] = list[l] < list[m] ? list[l++] : list[m++];

	// �����ִ°� �� �ִ� ����
	if (l == mid+1)
		for (; m <= right; m++,i++)
			Tmp[i] = list[m];
	else
		for (; l <= mid; l++,i++)
			Tmp[i] = list[l];
	//�ӽ� ���� �������� ���� ����Ʈ�� ����
	for (i = 0; i <= right - left; i++)
		list[i + left] = Tmp[i];
}
void MergeSorting(int list[],int ar[], int left, int right){
	//�ݾ� �����鼭 ���ȣ���� �̿��Ͽ� �պ��� ����
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
