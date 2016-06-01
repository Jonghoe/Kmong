#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "sort.h"

#define ASC   1
#define DESC  2

typedef void SortFunc(int list[], int n);

void Generate(int list[], int n, int method) {
	for(int i = 0; i < n; i++) {
		if (method == ASC) 
			list[i] = i;
		else if (method == DESC) 
			list[i] = n - i - 1;
		else 
			list[i] = rand() % n;
	}
}

void Print(int list[], int n) {
	if (n > 20) 
		return;
	for(int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void Swap(int list[], int i, int j) {
	int temp = list[j];
	list[j] = list[i];
	list[i] = temp;
}

void simul(SortFunc* sort, char name[], int list[], int n) {
	int* data = (int*) malloc(sizeof(int) * n);
	memcpy(data, list, sizeof(int) * n);
	clock_t begin, end;
	double elapsed;
	begin = clock();
	sort(data, n);
	end = clock();
	elapsed = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	Print(data, n);
	free(data);
	printf("%12s : %10.2fms\n", name, elapsed);
}
int main(int argc, char* argv[]){
	int n =19;
	int method = 0;
	srand(time(0));
	if (argc >= 2) 
	n = atoi(argv[1]);

	if (argc >= 3) 
		method = atoi(argv[2]);

	int* list = (int*) malloc(sizeof(int) * n);
	Generate(list, n, method);
	Print(list, n);
	simul(QuickSort, "QuickSort", list, n);
	simul(BubbleSort, "Bubble", list, n);
	simul(SelectSort, "SelectSort", list, n);
	simul(InsertionSort, "InsertionSort", list, n);
	simul(MergeSort, "MergeSort", list, n);
	simul(RadixSort, "RadixSort", list, n);
	simul(HeapSort, "HeapSort", list, n);

	free(list);
	
	
}
