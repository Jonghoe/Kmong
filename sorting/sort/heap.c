#include "sort.h"
#include <stdlib.h>

void Make_Max_Heap(int list[], int n){
	int i = 1;
	for (; i < n; i++)
		if (i >= 2 && list[i / 2] < list[i]){
			Swap(list, i / 2, i);
			i = i / 2 - 1;
		}
}
void HeapSort(int list[], int n) {
	int i;
	int* Tmp = (int*)malloc(sizeof(int)*(n + 1));
	for (i = 0; i < n; i++)
		Tmp[i + 1] = list[i];
	//최대 힙 생성
	Make_Max_Heap(Tmp, n + 1);
	
	//루트 노드와 말단 노드 자리 바꾼후 바뀐 말단 노드는 범위에서 제외
	//이 과정 반복 후 길이 1이되면 멈춤
	for (i = n ; i > 0; i--){
		Swap(Tmp, i, 1);
		Make_Max_Heap(Tmp,i);
	}

	for (i = 0; i < n; i++)
		list[i] = Tmp[i + 1];
	free(Tmp);
}
