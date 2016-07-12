#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Len 11
typedef struct tag_Edge Edge;
typedef struct tag_Graph Graph;
typedef struct tag_Node Node;
typedef struct tag_Element Element;
typedef struct tag_Queue Queue;
typedef struct tag_Order Order;
//�ִܰŸ��� ��θ� ������ ����ü
struct tag_Order{
	int Order[10];
	int Head;
	int Tail;
	int size;
};

//������ ���� (����)
struct tag_Element{
	//����� �̸�
	char Name[11];
	//����� �ε��� ��
	int Index;
	//�� ��忡�� ����ϴ� �ִܰŸ� ����
	int Shortest[10];
	//�� ��忡�� ����ϴ� �ִܰŸ� ���
	Order OrderList[10];
};
struct tag_Edge{
	//�o���� ó���� ��
	int Start, End;
	//���� �ش��ϴ� ��带 ����Ŵ
	Node* Next;
	//����ġ ��
	int Value;
};
//��� ����ü
struct tag_Node{
	//����
	Element e;
	//�o��
	Edge edge[10];
};
//�o��
//�ִܰŸ��� ã������ ť
struct tag_Queue{
	Edge *Data[100];
	int Head;
	int Tail;
	int size;
};
//�׷���
struct tag_Graph{
	Node Vertex[10];
	int size;
};
//ť�� ������� Ȯ��
int IsEmpty_Queue(Queue* que){
	return que->size == 0;
}
void Init_Order(Order* ord, int Num){
	int i;
	for (i = 0; i < Num; i++)
		ord->Order[i] = 0;
	ord->Head = ord->size = ord->Tail = 0;
}
void Push_Order(Order* ord, int Index){
	ord->Order[ord->Tail++] = Index;
	++ord->size;
}
int Pop_Order(Order* ord){
	return ord->Order[ord->Head++];
	--ord->size;
}
void Copy_Order(Order* dst, Order* src){
	int i;
	dst->Tail = dst->Head;
	dst->size = 0;
	for (i = 0; i < src->size; i++)
		Push_Order(dst, src->Order[src->Head + i]);
}
//ť�� �����͸� ����
void Push_Queue(Queue* que,Edge* Data){
	que->Data[que->Tail++] = Data;
	que->size++;
}
//ť���� �����͸� ����
Edge* Pop_Queue(Queue* que){
	if (IsEmpty_Queue(que))
		return -1;
	que->size--;
	return que->Data[que->Head++];
}
//ť �ʱ�ȭ
void Init_Queue(Queue* que){
	que->Tail = que->size = que->Head = 0;
}
//�޴� ���
void Print_Menu(){
	printf("1.Input graph menu\n");
	printf("2.Cumputer the shortest paths menu\n");
	printf("3.Quit menu\n");
}
//�޴� ����
int Select_Menu(){
	int Ret_V;
	do{ scanf("%d", &Ret_V); } 
	while (!(1 <= Ret_V && Ret_V <= 3));
	return Ret_V;
}
//���ڿ����� ���� �ϳ��� ��ġ�� ã�Ƴ� ���� ��
int MyStrChr(char* str, char ch){
	int Ret_V, i;
	for (i = 0; *str != NULL && *str != ch; str++,i++);
	if (*str == NULL)
		return -1;
	return i;
}
//�׷������� Name�� �̸��� ������ ��带 ã�Ƴ�
Node* Find_Node(char* Name, Graph* graph){
	int i;
	for (i = 0; i < graph->size&&strcmp(graph->Vertex[i].e.Name, Name); i++);
	if (i == graph->size)
		return NULL;
	return &(graph->Vertex[i]);
}
//�׷����� ���ؽ��� �������
void Input_Vertex(Graph* graph){
	int i,k;
	for (i = 0; i < graph->size; i++){
		int j;
		//���ؽ��� �̸��� �ް�
		scanf("%s", graph->Vertex[i].e.Name);
		//������ ������ ���� �� �ʱ�ȭ 
		graph->Vertex[i].e.Index = i;
		for (j = 0; j < graph->size; j++){
			graph->Vertex[i].edge[j].Next = NULL;
			graph->Vertex[i].edge[j].Start = i;
			graph->Vertex[i].edge[j].End = j;
			graph->Vertex[i].edge[j].Value = 0;
			graph->Vertex[i].e.Shortest[j] = 0;
			Init_Order(&graph->Vertex[i].e.OrderList[j], graph->size);
		}
	}
}
//�׷����� �o�� �Է�
void Input_Edges(Graph* graph,int Num){
	int i;
	for (i = 0; i < Num; i++){
		char Tmp[100], A[Len];
		int j, _i,dist;
		Node* F_N, *S_N;
		scanf("%s", Tmp);
		scanf("%d", &dist);
		j = MyStrChr(Tmp, '-');
		strncpy(A, Tmp, j);
		A[j] = 0;
		F_N = Find_Node(A, graph,graph->size );
		S_N = Find_Node(Tmp+j+1, graph,graph->size );
		F_N->edge[S_N->e.Index].Next = S_N;
		F_N->edge[S_N->e.Index].End = S_N->e.Index;
		S_N->edge[F_N->e.Index].Next = F_N;
		S_N->edge[F_N->e.Index].End = F_N->e.Index;
		F_N->edge[S_N->e.Index].Value = dist;
		S_N->edge[F_N->e.Index].Value = dist;
	}
}
//ť ���� (�o���� ����ġ�� �������� ���� ���� ������ ������ )
void Sorting_Queue(Queue* que, int*Check, int Num){
	int i, j,k;
	for (i = que->Head; i != que->Tail; i++)
		for (j = i + 1; j != que->Tail; j++)
			if ( que->Data[j]->Value < que->Data[j - 1]->Value){
				Edge* Tmp = que->Data[j];
				que->Data[j] = que->Data[j - 1];
				que->Data[j - 1] = Tmp;
			}
}
//�׷��� ����
void Create_Graph(Graph* graph){
	int N, M,i;
	scanf("%d %d", &N, &M);
	graph->size = N;
	Input_Vertex(graph);
	Input_Edges(graph, M);
}
//�ִܰŸ� ����� �Լ�
void Make_Shortest(Graph* graph,Node* First,int Num){
	int i;
	//Ȯ���� ��带 �����ϱ����� üũ
	int Check[10];
	Queue que;
	for (i = 0; i < Num; i++)
		Check[i] = 0;
	//ť �ʱ�ȭ
	Init_Queue(&que);
	//ó�� ��忡�� �� ���� �� �� �ִ� ��� ����
	for (i = 0; i < Num; i++)
		if (First->edge[i].Value != 0){
			Push_Queue(&que, &First->edge[i]);
			First->e.Shortest[i] = First->edge[i].Value;
			Push_Order(&First->e.OrderList[i], First->e.Index);
			Push_Order(&First->e.OrderList[i], i);
		}
	// ù ��� Ȯ�� 
	Check[First->e.Index] = 1;
	// ù ��忡�� �� �� �ִ� ��θ� �����Ͽ� ���� ª�� �Ÿ��� �o���� �տ� ������ ����
	Sorting_Queue(&que, Check, Num);
	while (!IsEmpty_Queue(&que)){
		//�o�� ������ �� �o���� ���� ������ �ִܰŸ��� Ȯ��
		Edge* Now = Pop_Queue(&que);
		Check[Now->End] = 1;
		for (i = 0; i < Num; i++){
			//�� �o���� �� ��忡�� �� �� �ְ� �ִܰŸ��� Ȯ������ ���� ����̸� ť�� ����
			if (Check[i] == 0 && graph->Vertex[Now->End].edge[i].Value != 0)
				Push_Queue(&que, &(graph->Vertex[Now->End].edge[i]));
			//�׸��� ( ���� ������ �o���� �� ��� �ִܰŸ� + �o���� �� ��忡�� ���� ��� ������ �Ÿ�) ��
			//���������� �o���� �� ��忡�� ���� ������ ���� �ִ� �Ÿ��� ���Ͽ� ���ڰ� ª����� �ִܰŸ� ��ü
			if (i != First->e.Index &&graph->Vertex[Now->End].edge[i].Value != 0)
				if (First->e.Shortest[i] == 0){
					First->e.Shortest[i] = First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value;
					//���� ���� �� ���� ��� �� ����
					Copy_Order(&First->e.OrderList[i], &First->e.OrderList[Now->End]);
					Push_Order(&First->e.OrderList[i], i);
				}
				else if (First->e.Shortest[i] > First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value){
					First->e.Shortest[i] = First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value;
					Copy_Order(&First->e.OrderList[i], &First->e.OrderList[Now->End]);
					Push_Order(&First->e.OrderList[i], i);
				}
		}
		// �o���� ���� ���� ������ ����
		Sorting_Queue(&que, Check, Num);
	}
}

Node* Select_Shortest(Graph* graph){
	char Tmp[100];
	Node* Dst;
	scanf("%s", Tmp);
	Dst = Find_Node(Tmp, graph, graph->size);
	if (Dst != NULL)
		Make_Shortest(graph, Dst, graph->size);
	return Dst;
}

void Print_Shortest(Graph* graph,int First, int Num){
	int i = 0,j;
	Element* F_E = &graph->Vertex[First].e;
	for (i = 0; i < Num; i++){
		if (i != First){
			printf("%s : ", graph->Vertex[i].e.Name);
			printf("%d ", F_E->Shortest[i]);
			printf("path ");
			for (j = F_E->OrderList[i].Head; j != F_E->OrderList[i].Tail; j++)
				printf("%s ", graph->Vertex[F_E->OrderList[i].Order[j]].e.Name);
			printf("\n");
		}
	}
	printf("\n");
}
int main(){
	int Select,Exit = 1;
	Node* Dst;
	do{
		Graph graph;
		Print_Menu();
		switch (Select_Menu()){
		case 1:
			Create_Graph(&graph);
			break;
		case 2:
			Dst = Select_Shortest(&graph);
			Print_Shortest(&graph,Dst->e.Index,graph.size);
			break;
		case 3:
			Exit = 0;
			break;
		}

	} while (Exit);
}