#include "sort.h"

void SelectSort(int list[], int n) {
	int i,j,min,min_L;
	for (i = 0; i < n; i++) {
		// ������ ���� ���� ���� ������ ���� ��ġ�� ��������
		min = list[i];
		min_L = i;
		// ���� �������� ã�� ���� �ݺ���
		for(j = i; j < n; j++) 
			if (min > list[j]){
				min = list[j];
				min_L = j;
			}
		// ���� ���� ���� ��ġ �ٲ�
		Swap(list, i, min_L);
    }
 }
