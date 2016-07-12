#include"Console_Function.h"
#include<Windows.h>
int Key_Push(){
	char Buffer[2];
	Buffer[1] = 0;
	do{
		Buffer[0] = getch();
	} while (!isdigit(Buffer[0]));
	return atoi(Buffer);
}

void iToS(int INT, char* string){
	char Tmp[100];
	INT /= 10000;
	itoa(INT, Tmp, 10);
	strcat(Tmp, "만 원");
	strcpy(string, Tmp);
}
//텍스트 색깔 변경
void setcolor(int color, int bgcolor){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}

//커서 위치 변경
void gotoxy(int x, int y){
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
//x , y 위치에 문자 출력
void gotoPrint(int x, int y, char *m){
	gotoxy(x, y);
	puts(m);
}
void Color_Change(int Turn){
	switch (Turn){
	case 0:	setcolor(PLAYER_1_Color, 0); break;
	case 1: setcolor(PLAYER_2_Color, 0); break;
	}
}
//도시 정보 출력
void Print_City_Info(int x, int y, City* city){
	char Name[100];
	char Price[4][100];
	char Fine[4][100];
	int i;
	strcpy(Name, "도시 이름 : ");
	strcat(Name, city->Name);
	if (city->Special == NULL){
		strcpy(Price[0], "가격 : ");
		for (i = 1; i < 4; i++)
			iToS(city->Price[i - 1], Price[i]);

		strcpy(Fine[0], "통행료 : ");
		for (i = 1; i < 4; i++)
			iToS(city->Fine[i - 1], Fine[i]);
		gotoPrint(x, y, Name);
		gotoPrint(x, y + 1, Price[0]);
		gotoPrint(x, y + 2, Price[1]);
		gotoPrint(x, y + 3, Price[2]);
		gotoPrint(x, y + 4, Price[3]);
		gotoPrint(x, y + 5, Fine[0]);
		gotoPrint(x, y + 6, Fine[1]);
		gotoPrint(x, y + 7, Fine[2]);
		gotoPrint(x, y + 8, Fine[3]);
	}
}
//빌딩 하나당 □ 출력 
void Building_Draw(City* city, Player* player, int Turn){
	int i = 0;
	Color_Change(Turn);
	for (i = 0; i <= city[player[Turn].Loc].level; i++)
		gotoPrint(city[player[Turn].Loc].LT.X + 2 + (i * 2), city[player[Turn].Loc].LT.Y + 2, "□");
}
void Building_Clear(City* city, Player* player, int Turn){
	int i = 0;
	Color_Change(Turn);
	for (i = 0; i <= city->level; i++)
		gotoPrint(city->LT.X + 2 + (i * 2), city->LT.Y + 2, "  ");
}

//player의 Loc 를 확인하여 그 위치에 있는 도시에 말을 그린다
void Piece_Draw(City* city, Player* player, int Turn){
	Color_Change(Turn);
	gotoPrint(city[player[Turn].Loc].LT.X + 2 + (Turn * 3), city[player[Turn].Loc].LT.Y + 1, "○");
}
//player의 Loc를 확인하여 그 위치에 있는 도시에 그려진 말을 지운다.
void Piece_Clear(City* city, Player* player, int Turn){
	gotoPrint(city[player[Turn].Loc].LT.X + 2 + (Turn* 3), city[player[Turn].Loc].LT.Y + 1, "  ");
}
// 지우기 원하는 부분의 그림을 지운다.
void Line_Claer(int y){
	gotoPrint(18, y, "\t\t\t\t\t\t\t\t\t\t\t\t");
}
// 실행창의 화면을 모두 지운다.
void Board_Clear(){
	int i = 0;
	for (i = 10; i < 28; i++)
		Line_Claer(i);
}
//기본 게임 판 출력
void Print_Base_Board(){
	int i = 0, j, Loc, Line = 2;
	setcolor(15, 0);
	system("mode con:cols=160lines=50");
	printf("\n");
	printf("┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐\n");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	printf("├─        ─┼──────┴──────┴──────┴──────┴──────┴──────┴──────┼─\t    ─┤\n"); Line++;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 4; j++){
			gotoPrint(0, Line, "│"); gotoPrint(14, Line, "│"); gotoPrint(112, Line, "│"); gotoPrint(126, Line++, "│");
		}
		printf("├─        ─┤  \t\t\t\t\t\t\t\t\t\t\t\t├─\t    ─┤\n"); Line++;
	}
	for (i = 0; i < 4; i++){
		gotoPrint(0, Line, "│"); gotoPrint(14, Line, "│"); gotoPrint(112, Line, "│"); gotoPrint(126, Line++, "│");
	}
	printf("├─        ─┼──────┬──────┬──────┬──────┬──────┬──────┬──────┬─\t    ─┤\n"); Line++;
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	gotoPrint(0, Line, "│"); gotoPrint(126, Line++, "│");
	printf("└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘\n");
	Loc = 1;
	//사용자 칸
	for (j = 0; j < 2; j++){
		gotoPrint(130, Loc++, "┌─────────────┐");
		for (i = 0; i < 13; i++)
			gotoPrint(130, Loc++, "│\t\t\t      │");
		gotoPrint(130, Loc++, "└─────────────┘");
	}
}

//배경화면 편집
void BG_Upgrade(City* city, Player* player){
	int i = 0, j;
	//플레이어 1의 색깔 : 파랑
	//플레이어 2의 색깔 : 빨강
	for (i = 0; i < 2; i++){
		char Tmp[100];
		char Player[100] = "Player";
		char Turn[100] = "Circle : ";
		char Money[100] = "Money : ";
		char Block[100] = "Block : ";
		Color_Change(i);
		gotoPrint(city[player[i].Loc].LT.X + 2 + (i * 3), city[player[i].Loc].LT.Y + 1, "○");
		strcat(Player, itoa(i, Tmp, 10));
		gotoPrint(132, 2 + i * 15, Player);
		itoa(player[i].Turn_Count, Tmp, 10);
		strcat(Turn, Tmp);
		gotoPrint(132, 3 + i * 15, Turn);
		//itoa(player[i].Money, Tmp, 10);
		iToS(player[i].Money, Tmp);
		strcat(Money, Tmp);
		gotoPrint(132, 4 + i * 15, Money);
		itoa(player[i].Block, Tmp, 10);
		strcat(Block, Tmp);
		gotoPrint(132, 5 + i * 15, Block);
	}
	//배경 화면 색 : 흰색
	for (i = 0; i < CITY_NUM; i++){
		char Name[100];
		char Tmp[100];
		setcolor(15, 0);
		strcpy(Name, city[i].Name);
		itoa(i, Tmp, 10);
		strcat(Name, Tmp);
		gotoPrint(city[i].LT.X, city[i].LT.Y, Name);
		//화면에 나타나는 금액 표시
		if (city[i].Special == NULL){
			if (city[i].Owner == &player[0])
				Color_Change(0);
			else if (city[i].Owner == &player[1])
				Color_Change(1);

			if (city[i].Owner !=NULL)
			for (j = 0; j <= city[i].level; j++)
				gotoPrint(city[i].LT.X + 2 + (j * 2), city[i].LT.Y + 2, "□");
			setcolor(15, 0);
			iToS(city[i].Price[city[i].level + 1], Name);
			gotoPrint(city[i].LT.X, city[i].LT.Y + 3, Name);
		}
	}
}
void Print_Menu(Player* player, City* city, int Turn){
	int Select;
	Board_Clear();
	do{
		gotoPrint(45, 15, "1. 주사위를 굴린다.");
		gotoPrint(45, 16, "2. 도시 정보 확인.");
		gotoPrint(45, 17, "3. 세이브 후 종료");
		gotoPrint(45, 18, "0. 파산.");
		Select = Select_Menu(player, city, Turn);
	} while (Select != 1 && Select != 0);
}

void Start_Screen(int* Type){
	int Select;
	gotoPrint(45, 15,"1 . 새 게임");
	gotoPrint(45, 16,"2 . 게임 불러오기");
	Select = getch();
	if (Select == '1')
		*Type = 1;
	else if (Select == '2')
		*Type = 2;
}