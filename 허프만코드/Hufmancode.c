#include<stdio.h>
#define MAX_ELEMENT 100
typedef struct TreeNode {
	int weight;
	struct TreeNode *left_child;
	struct TreeNode *right_child;
} TreeNode;

typedef struct {
	TreeNode *ptree;
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 초기화 함수
init(HeapType *h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_min_heap(HeapType *h, element item)
{
	int j, i = 0,k=0;
	TreeNode* Tmp = item.ptree;
	for (; Tmp->right_child != NULL; Tmp = Tmp->right_child,k=1);
	h->heap[++h->heap_size] = item;
	for (i = h->heap_size; i <= h->heap_size;){
		if (i >1 && (k != 1 ||h->heap_size !=3)){
		TreeNode* Tmp1 = h->heap[i].ptree;
		TreeNode* Tmp2 = h->heap[i/2].ptree;
		for (; Tmp1->right_child != NULL; Tmp1 = Tmp1->right_child);
		for (; Tmp2->right_child != NULL; Tmp2 = Tmp2->right_child);
		if (Tmp2->weight > Tmp1->weight){
			element Tmp;
			Tmp = h->heap[i];
			h->heap[i] = h->heap[i / 2];
			h->heap[i / 2] = Tmp;
			i = i / 2;
		}
		else
			i++;
		}
		else
			i++;
	}
	
	/*for (; i < h->heap_size&&h->heap[i].key > Tmp->weight ; i++);
	h->heap[h->heap_size].key = item.key;
	h->heap[h->heap_size].ptree = item.ptree;
	if (i!=h->heap_size++)
		for (j = h->heap_size - 1; j != i; j--){
			element Tmp;
			Tmp = h->heap[j];
			h->heap[j] = h->heap[j - 1];
			h->heap[j - 1] = Tmp;
		}
	*/
}
// 삭제 함수
element* delete_min_heap(HeapType *h)
{
	int E = h->heap_size;
	int i = 0;
	element Tmp= h->heap[1];
	h->heap[1] = h->heap[h->heap_size];
	h->heap[h->heap_size--] = Tmp;
	for (i = 2; i <= h->heap_size; i++){
		if (i>1&&h->heap[i / 2].key > h->heap[i].key){
			element Tmp;
			Tmp = h->heap[i];
			h->heap[i] = h->heap[i / 2];
			h->heap[i / 2] = Tmp;
		}
	}
	return &h->heap[E];
}
// 이진 트리 생성 함수
TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL){
		fprintf(stderr, "메모리 에러\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}
// 이진 트리 제거 함수
void destroy_tree(TreeNode *root)
{
	if (root == NULL) return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root);
}
int Make_Huffman(TreeNode** Root, int det,int* hufman,int Ord){
	if (*Root == NULL)
		return 0;
	if ((*Root)->weight == det)
		return 1;
	hufman[Ord] = 1;
	if (Make_Huffman(&((*Root)->left_child), det, hufman, Ord+1) == 1)
		return 1;
	else{
		hufman[Ord] = 0;
		if (Make_Huffman(&((*Root)->right_child), det, hufman, Ord + 1) == 1)
			return 1;
	}
	hufman[Ord] = -1;
	return 0;
}
void Print_huffman_Tree(element* Tree,int freq[],int n){
	int i = 0,j;
	int* Hufman = (int*)malloc(sizeof(int)*n);
	for (i=0; i < n; i++)
		Hufman[i] = -1;
	for (i=0; i < n; i++){
		Make_Huffman(&(Tree->ptree), freq[i], Hufman, 0);
		printf("%d ", freq[i]);
		for (j = 0; j < n&& Hufman[j] != -1; j++)
			printf("%d", Hufman[j]);
		printf("\n");
	}

}
// 허프만 코드 생성 함수
void huffman_tree(int freq[], int n)
{
	int i;
	TreeNode *node, *x;
	HeapType heap;
	element e, e1, e2;
	init(&heap);
	for (i = 0; i<n; i++){
		node = make_tree(NULL, NULL);
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(&heap, e);
	}
	for (i = 1; i<n; i++){
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = *delete_min_heap(&heap);
		e2 = *delete_min_heap(&heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(&heap, e);
	}
	e = *delete_min_heap(&heap); // 최종 트리
	Print_huffman_Tree(&e, freq, n);
	destroy_tree(e.ptree);
}
// 주함수
void main()
{
	int freq[] = { 15, 12, 8, 6, 4 };
	huffman_tree(freq, 5);
}
