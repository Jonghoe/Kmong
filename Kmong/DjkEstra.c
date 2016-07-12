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
//최단거리의 경로를 저장할 구조체
struct tag_Order{
	int Order[10];
	int Head;
	int Tail;
	int size;
};

//노드들의 원소 (정보)
struct tag_Element{
	//노드의 이름
	char Name[11];
	//노드의 인덱스 값
	int Index;
	//이 노드에서 출발하는 최단거리 값들
	int Shortest[10];
	//이 노드에서 출발하는 최단거리 경로
	Order OrderList[10];
};
struct tag_Edge{
	//엗지의 처음과 끝
	int Start, End;
	//끝에 해당하는 노드를 가르킴
	Node* Next;
	//가중치 값
	int Value;
};
//노드 구조체
struct tag_Node{
	//원소
	Element e;
	//엗지
	Edge edge[10];
};
//엗지
//최단거리를 찾기위한 큐
struct tag_Queue{
	Edge *Data[100];
	int Head;
	int Tail;
	int size;
};
//그래프
struct tag_Graph{
	Node Vertex[10];
	int size;
};
//큐가 비었는지 확인
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
//큐에 데이터를 넣음
void Push_Queue(Queue* que,Edge* Data){
	que->Data[que->Tail++] = Data;
	que->size++;
}
//큐에서 데이터를 빼냄
Edge* Pop_Queue(Queue* que){
	if (IsEmpty_Queue(que))
		return -1;
	que->size--;
	return que->Data[que->Head++];
}
//큐 초기화
void Init_Queue(Queue* que){
	que->Tail = que->size = que->Head = 0;
}
//메뉴 출력
void Print_Menu(){
	printf("1.Input graph menu\n");
	printf("2.Cumputer the shortest paths menu\n");
	printf("3.Quit menu\n");
}
//메뉴 선택
int Select_Menu(){
	int Ret_V;
	do{ scanf("%d", &Ret_V); } 
	while (!(1 <= Ret_V && Ret_V <= 3));
	return Ret_V;
}
//문자열에서 문자 하나의 위치를 찾아냄 가장 앞
int MyStrChr(char* str, char ch){
	int Ret_V, i;
	for (i = 0; *str != NULL && *str != ch; str++,i++);
	if (*str == NULL)
		return -1;
	return i;
}
//그래프에서 Name의 이름을 가지는 노드를 찾아냄
Node* Find_Node(char* Name, Graph* graph){
	int i;
	for (i = 0; i < graph->size&&strcmp(graph->Vertex[i].e.Name, Name); i++);
	if (i == graph->size)
		return NULL;
	return &(graph->Vertex[i]);
}
//그래프에 버텍스를 집어넣음
void Input_Vertex(Graph* graph){
	int i,k;
	for (i = 0; i < graph->size; i++){
		int j;
		//버텍스의 이름을 받고
		scanf("%s", graph->Vertex[i].e.Name);
		//각각의 값들을 생성 및 초기화 
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
//그래프에 엗지 입력
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
//큐 정렬 (엗지의 가중치를 기준으로 작은 값이 앞으로 오도록 )
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
//그래프 생성
void Create_Graph(Graph* graph){
	int N, M,i;
	scanf("%d %d", &N, &M);
	graph->size = N;
	Input_Vertex(graph);
	Input_Edges(graph, M);
}
//최단거리 만드는 함수
void Make_Shortest(Graph* graph,Node* First,int Num){
	int i;
	//확정된 노드를 구분하기위한 체크
	int Check[10];
	Queue que;
	for (i = 0; i < Num; i++)
		Check[i] = 0;
	//큐 초기화
	Init_Queue(&que);
	//처음 노드에서 한 번에 갈 수 있는 경로 설정
	for (i = 0; i < Num; i++)
		if (First->edge[i].Value != 0){
			Push_Queue(&que, &First->edge[i]);
			First->e.Shortest[i] = First->edge[i].Value;
			Push_Order(&First->e.OrderList[i], First->e.Index);
			Push_Order(&First->e.OrderList[i], i);
		}
	// 첫 노드 확정 
	Check[First->e.Index] = 1;
	// 첫 노드에서 갈 수 있는 경로를 정렬하여 가장 짧은 거리의 엗지가 앞에 오도록 설정
	Sorting_Queue(&que, Check, Num);
	while (!IsEmpty_Queue(&que)){
		//엗지 빼내고 그 엗지의 도착 지점은 최단거리로 확정
		Edge* Now = Pop_Queue(&que);
		Check[Now->End] = 1;
		for (i = 0; i < Num; i++){
			//그 엗지의 끝 노드에서 갈 수 있고 최단거리로 확정되지 않은 노드이면 큐에 삽입
			if (Check[i] == 0 && graph->Vertex[Now->End].edge[i].Value != 0)
				Push_Queue(&que, &(graph->Vertex[Now->End].edge[i]));
			//그리고 ( 시작 점에서 엗지의 끝 노드 최단거리 + 엗지의 끝 노드에서 다음 노드 까지의 거리) 와
			//시작점에서 엗지의 끝 노드에서 다음 노드까지 현재 최단 거리와 비교하여 전자가 짧은경우 최단거리 교체
			if (i != First->e.Index &&graph->Vertex[Now->End].edge[i].Value != 0)
				if (First->e.Shortest[i] == 0){
					First->e.Shortest[i] = First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value;
					//순서 복사 및 현재 노드 값 삽입
					Copy_Order(&First->e.OrderList[i], &First->e.OrderList[Now->End]);
					Push_Order(&First->e.OrderList[i], i);
				}
				else if (First->e.Shortest[i] > First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value){
					First->e.Shortest[i] = First->e.Shortest[Now->End] + graph->Vertex[Now->End].edge[i].Value;
					Copy_Order(&First->e.OrderList[i], &First->e.OrderList[Now->End]);
					Push_Order(&First->e.OrderList[i], i);
				}
		}
		// 엗지의 가장 잡은 값으로 정렬
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