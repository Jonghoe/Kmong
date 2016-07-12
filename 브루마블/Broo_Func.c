#include"Broo_Type.h"
#include"Broo_Func.h"
#include"Console_Function.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
//황금 열쇠의 함수
//랜덤 값을 이용 총 6개의 경우 수 
void Start_Func(City* city, Player* player, int Turn){
	Board_Clear();
	gotoPrint(45, 18, "출발 점 보너스 (+ 2000000)");
	player[Turn].Money += 2000000;
	player[Turn].Turn_Count++;
	BG_Upgrade(city, player);
	getch();
}
//MT지역 함수
void MT_Func(City* city, Player* player, int Turn){
	gotoPrint(45, 15, "MT지역에 도착하였습니다. 3일간 고주망태가 됩니다. ");
	player[Turn].Block = 2;
	getch();
}
//셔틀버스 함수 
void ShuttleBus_Func(City* city, Player* player, int Turn){
	// 움직이기 전 지역 이랑 비교해서 한바퀴 돌경우를 구별하기 위해서
	int Prev = player[Turn].Loc;
	char Buff[100];
	int I;
	Board_Clear();
	gotoPrint(45, 15, "이동할 지역 번호를 입력해 주십시오. ");
	Piece_Clear(city, player, Turn);
	do{
		fflush(stdin);
		Line_Claer(17);
		gotoxy(45, 17);
		scanf("%s", Buff);
		I = atoi(Buff);
	} while (!(48 <= Buff[0] && Buff[0] <= 57) || I >= CITY_NUM);
	player[Turn].Loc = atoi(Buff);
	//한바퀴 돈경우
	if (Prev > player[Turn].Loc)
		city[0].Special(city, player, Turn);

	//말을 그림
	Piece_Draw(city, player, Turn);
	//그 땅에서 위치에서 할 일 수행
	if (city[player[Turn].Loc].Special != NULL)
		city[player[Turn].Loc].Special(city, player, Turn);
	// 그 땅 주인을 물음 없을 시 구매   있을 시 통행료 납부
	else if (city[player[Turn].Loc].Owner == NONE)
		Buy_City(city, player, Turn);
	else if (city[player[Turn].Loc].Owner != player)
		Pay_Fine(city, player, Turn);
}
void Festival_Func(City* city, Player* player, int Turn){
	char Buff[100];
	int Val, i;
	Board_Clear();

	gotoPrint(45, 15, "대학교 축제 (임의의 지역 가격 2배)");
	gotoPrint(45, 16, "원하시는 지역을 입력하여 주십시오.");
	do{
		Line_Claer(17);
		gotoxy(45, 17);
		scanf("%s", Buff);
		Val = atoi(Buff);
	} while (!(49 <= Buff[0] && Buff[0] <= 57) || Val >= CITY_NUM || city[Val].Owner == NULL);
	Board_Clear();
	itoa(Val, Buff, 10);
	strcat(Buff, "지역이 축제 상태가 되었습니다.  || 통행료 * 2");
	getch();
	Board_Clear();
	for (i = 0; i < 3; i++)
		city[Val].Fine[i] *= 2;

}
void Gold_Key_Func(City* city, Player* player, int Turn){
	int Gold = rand() % 6;;
	Board_Clear();
	switch (Gold){
	case 0:
		gotoPrint(45, 18, "장학금 지급 (+ 300만)");
		player[Turn].Money += 3000000;
		break;
	case 1:
		gotoPrint(45, 18, "등록금 내는 날 (- 150만) ");
		player[Turn].Money -= 1500000;
		break;
	case 2:
		Piece_Clear(city, player, Turn);
		gotoPrint(45, 18, "운수 좋은 날 셔틀버스가 바로 내 눈 앞에");
		gotoPrint(45, 18, "(셔틀 버스 지역으로 이동)");
		player[Turn].Loc = 23;
		city[player[Turn].Loc].Special(city, player, Turn);
		Piece_Draw(city, player, Turn);
		break;
	case 3:
		gotoPrint(45, 18, "학교 기물 파손 (- 30 만)");
		player[Turn].Money -= 300000;
		break;
	case 4:
		gotoPrint(45, 18, "자취방 월세 내는 날 (- 70만)");
		player[Turn].Money -= 700000;
		break;
	case 5:
		Piece_Clear(city, player, Turn);
		gotoPrint(45, 18, "오늘은 MT가는 날 2일동안 술 마시기");
		gotoPrint(45, 18, "(MT지역으로 이동)");
		player[Turn].Loc = 8;
		city[player[Turn].Loc].Special(city, player, Turn);
		Piece_Draw(city, player, Turn);
		break;
	}
	getch();
}
//플레이어의 값 초기화
void Init_Player(Player* Player, City* city, int Turn){
	Player[Turn].Block = 0;
	Player[Turn].Money = 5000000;
	Player[Turn].Turn_Count = 0;
	Player[Turn].Loc = 0;
	Player[Turn].Give_Up = 0;
	Player[Turn].Retry = 0;
}
//도시의 정보 초기화 파일 입출력을 통해서 도시의 정보를 넣는다.
//단 특별한경우는 제외 ex) 황금열쇠, MT, 스쿨 버스
void Init_City(City* city){
	enum Move { UP, RIGHT, DOWN, LEFT };
	int Dir = LEFT;
	FILE* fo = fopen("BrooMable.txt", "r");
	int Move = 0;
	char Buffer[1024];
	int i = 0, j, M = 0;
	if (fo == NULL)
		return NULL;
	//--------------------첫 출발 점 초기화-----------------------
	strcpy(city[0].Name, "출발지점");
	city[0].Owner = NONE;
	city[0].LT.X = 114;
	city[0].LT.Y = 37;
	city[0].Special = Start_Func;

	//-----------------------------------------------------------
	for (i = 1; i < CITY_NUM; i++){
		//도시의 왼쪽위 좌표를 나타냄 ( 맵상에 그리기 위해서 )
		switch (Dir){
		case UP:
			city[i].LT.Y = city[i - 1].LT.Y + 5;
			city[i].LT.X = city[i - 1].LT.X;
			break;
		case RIGHT:
			city[i].LT.X = city[i - 1].LT.X + 14;
			city[i].LT.Y = city[i - 1].LT.Y;
			break;
		case DOWN:
			city[i].LT.Y = city[i - 1].LT.Y - 5;
			city[i].LT.X = city[i - 1].LT.X;
			break;
		case LEFT:
			city[i].LT.X = city[i - 1].LT.X - 14;
			city[i].LT.Y = city[i - 1].LT.Y;
			break;
		}
		//도시의 기본정보 입력
		fscanf(fo, "%s", city[i].Name);
		city[i].level = -1;
		city[i].Owner = NONE;
		//특수지역 함수 설정
		if (strcmp(city[i].Name, "황금열쇠") == 0)
			city[i].Special = Gold_Key_Func;
		else if (strcmp(city[i].Name, "MT지역") == 0)
			city[i].Special = MT_Func;
		else if (strcmp(city[i].Name, "셔틀버스") == 0)
			city[i].Special = ShuttleBus_Func;
		else if (strcmp(city[i].Name, "대학축제") == 0)
			city[i].Special = Festival_Func;
		// 그 외 도시 지역 가격 결정
		else{
			city[i].Special = NULL;
			for (j = 0; j < 3; j++){
				fscanf(fo, "%d", &M);
				city[i].Price[j] = M;
			}
			for (j = 0; j < 3; j++){
				fscanf(fo, "%d", &M);
				city[i].Fine[j] = M;
			}
		}
		//방향 변경
		if (i == 8 || i == 15 || i == 23)
			Dir--;
	}
	fclose(fo);
}
int Line_Monopoly(City* city, Player* player){
	int i, j, Owner1 = 0, Owner2 = 0;
	int Loc = 0;
	for (i = 0; i < 4; i++){
		Owner1 = Owner2 = 0;
		if (i % 2 == 0){
			for (j = 0; j < 8; j++)
				if (city[Loc + j].Special == NULL)
					if (city[Loc + j].Owner == &player[0])
						Owner1++;
					else if (city[Loc + j].Owner == &player[1])
						Owner2++;
			/*
			학점 출력  (리인 독점 )
			*/
			if (Owner1 == 6 || Owner2 == 6)
				return WIN;
		}
		else{
			for (j = 0; j < 7; j++)
				if (city[Loc + j].Special != NULL)
					if (city[Loc + j].Owner == &player[0])
						Owner1++;
					else if (city[Loc + j].Owner == &player[1])
						Owner2++;
			/*
			학점 출력  (리인 독점 )
			*/
			if (Owner1 == 6 || Owner2 == 6)
				return WIN;
		}
		Loc = Loc + j;
	}
	return PASS;
}

//도시 구매
void Buy_City(City* city, Player* player, int Turn){
	int Select;
	char Buff[100];
	char Result[100] = "구매가 완료 되었습니다. - ";
	//플레이어의 돈이 도시 최저 값보다 작을 경우 그냥 지나감
	if (city[player[Turn].Loc].Price[0]>player[Turn].Money)
		return;
	Board_Clear();
	gotoPrint(45, 15, "도시를 구매 하시겠습니까 ? 예 : 1 // 취소 : 0");
	Print_City_Info(45, 16, &city[player[Turn].Loc]);
	Select = Key_Push();
	Board_Clear();
	if (Select == 0){
		gotoPrint(45, 23, "구매가 취소 되었습니다");
		getch();
		return;
	}
	//도시구매 선택
	if (Select == 1)
		do{
			int Val;
			gotoPrint(45, 15, "몇 단계를 구매 하시겠습니까 ? //취소 : 0");
			Select = Key_Push();
			Board_Clear();
			if (Select == 0){
				gotoPrint(45, 15, "구매가 취소 되었습니다");
				getch();
				return;
			}
			//출발지점을 돈 횟수에 맞춰서 건물 레벨 제한
			else if (player[Turn].Turn_Count + 1 >= Select){
				iToS(city[player[Turn].Loc].Price[Select - 1], Buff);
				strcat(Result, Buff);
				gotoPrint(45, 15, Result);
				player[Turn].Money -= city[player[Turn].Loc].Price[Select - 1];
				city[player[Turn].Loc].Owner = &player[Turn];
				city[player[Turn].Loc].level = Select - 1;
				Building_Draw(city, player, Turn);
				getch();
				return;
			}
			//건물 레벨제한을 벗어날 경우
			else{
				gotoPrint(45, 15, "구매가 불가능 합니다.");
				getch();
			}
		} while (1);
}

//도시 판매 함수
void Sell_City(Player* player, City* city, int Turn){
	int i = 0,Line;
	int Select = 0;
	char Buff[100];
	int Val;
	//판매할 도시 선택
	while (1){
		Line = 16;
		Board_Clear();
		Color_Change(Turn);
		gotoPrint(45, 15, "판매하실 도시를 선택하여 주십시오. 판매 종료  : 0");
		for (i = 0; i < CITY_NUM; i++) 
			if ((city)[i].Owner == &player[Turn]){
				char Price[100];
				char Tmp[100];
				strcpy(Price, "판매가 : ");
				iToS(city[i].Price[city[i].level], Tmp);
				strcat(Price, Tmp);
				strcat(Price, " ");
				strcat(Price, city[i].Name);
				//gotoPrint(45, 15 + i * 2, city[i].Name);
				gotoPrint(45, ++Line  , Price);
			}
		do{
			Line_Claer(16);
			gotoxy(45, 16);
			scanf("%s", Buff);
			Val = atoi(Buff);
			if (Val == 0)
				break;
		} while (!(48 <= Buff[0] && Buff[0] <= 57) || Val >= CITY_NUM || city[Val].Owner != &player[Turn]);
		if (Val == 0){
			gotoPrint(45, ++Line, "판매가 완료 되었습니다.");
			getch();
			Line_Claer(Line);
			return;
		}
		//자기의 땅이 아닌경우
		else if (city[Val].Owner != &player[Turn]){
			gotoPrint(45, ++Line, "당신의 땅이 아닙니다.");
			getch();
			Line_Claer(Line);
		}
		//자기의 땅인 경우 땅을 판매
		else{
			city[Val].Owner = NONE;
			player[Turn].Money += city[Val].Price[city[Val].level];
			city[Val].level = -1;
			Building_Clear(&city[Val], player, Turn);
			gotoPrint(45, ++Line, "판매에 성공하였습니다.");
			getch();
			Line_Claer(Line);
			BG_Upgrade(city, player);
		}
	}
}
//통행료 납부 
void Pay_Fine(City* city, Player* player, int Turn){
	Board_Clear();
	//통행료보다 가진 돈이 없을 경우 땅 판매 
	if (city[player[Turn].Loc].Fine[city[player[Turn].Loc].level] > player[Turn].Money){
		gotoPrint(45, 15, "금액이 부족합니다  땅을 팔아 주십시오");
		getch();
		Board_Clear();
		Sell_City(player, city, Turn);
		//땅 판매 후에도 돈이 부족할 경우 파산으로 결정
		if (city[player[Turn].Loc].Fine[city[player[Turn].Loc].level] > player[Turn].Money)
			player[Turn].Give_Up = PASAN;
	}
	//플레이어가 파산이 아닌 경우 통행료를 납부하고 도시를 살 지 여부를 물음
	if (player[Turn].Give_Up != PASAN){
		char Fine[100];
		char Message[100];
		iToS(city[player[Turn].Loc].Fine[city[player[Turn].Loc].level], Fine);
		player[Turn].Money -= city[player[Turn].Loc].Fine[city[player[Turn].Loc].level];
		city[player[Turn].Loc].Owner->Money += city[player[Turn].Loc].Fine[city[player[Turn].Loc].level];
		BG_Upgrade(city, player);
		Color_Change(Turn);
		strcpy(Message, "통행료를 납부하였습니다 - ");
		strcat(Message, Fine);
		gotoPrint(45, 15, Message);
		getch();
		Board_Clear();
		Buy_City(city, player, Turn);
	}
}
int Quiet(City* city, Player* player, int* Turn, int Choose){
	if (Line_Monopoly(city, player) == WIN)
		return WIN;
	if (Choose == PASAN){
		CHANGE_TURN(*Turn, 2);
		return GG;
	}
	if (player[*Turn].Money < 0){
		Sell_City(player, city, *Turn);
		if (player[*Turn].Money < 0){
			CHANGE_TURN(*Turn, 2);
			return GG;
		}
	}
	return PASS;
}
int Roll_The_Dice(Player* player, int Turn){
	int Ret_V = 0, I;
	char Buff[100];
	char Tmp1[100] = "첫 번쨰 주사위 수 : ";
	char Tmp2[100] = "두 번쨰 주사위 수 : ";
	srand(time(NULL));
	I = (rand() % 25 * 125) % 6 + 1;
	//스트링값 문자열로 변경 후 출력
	itoa(I, Buff, 10);
	strcat(Tmp1, Buff);
	gotoPrint(45, 15, Tmp1);
	//
	Ret_V += I;
	I = (rand() % 25 * 125) % 6 + 1;
	//스트링값 문자열로 변경 후 출력
	itoa(I, Buff, 10);
	strcat(Tmp2, Buff);
	gotoPrint(45, 16, Tmp2);
	//
	//이전과 같은 값의 주사위가 나온 경우
	if (I == Ret_V){
		gotoPrint(45, 17, "Lucky!!!   One More");
		player[Turn].Retry = 1;
	}

	getch();
	Ret_V += I;
	Board_Clear();
	return Ret_V;
}
int Select_Menu(Player* player, City* city, int Turn){
	int Select;
	Select = Key_Push();
	Board_Clear();
	if (Select == 0){
		gotoPrint(45, 15, "플레이어가 파산을 선택 하셨습니다 .");
		player[Turn].Give_Up = PASAN;
	}
	else if (Select == 1){
		Piece_Clear(city, player, Turn);
		player[Turn].Loc = player[Turn].Loc + Roll_The_Dice(player, Turn);
		if (player[Turn].Loc >= 30){
			player[Turn].Loc = player[Turn].Loc %CITY_NUM;
			city[0].Special(city, player, Turn);
		}
		Piece_Draw(city, player, Turn);
	}
	else if (Select == 2){
		char City_Num[100];
		int Ret_V;
		gotoPrint(45, 15, "지역 번호를 입력 하십시오 ");
		do{
			fflush(stdin);
			Line_Claer(17);
			gotoxy(45, 17);
			scanf("%s", City_Num);
			Ret_V = atoi(City_Num);
		} while (!(49 <= City_Num[0] && City_Num[0] <= 57) || Ret_V >= CITY_NUM);
		Print_City_Info(45, 16, &city[Ret_V]);
		getch();
		Board_Clear();
	}
	else if (Select == 3){
		gotoPrint(45, 15, "데이터를 저장하고 종료합니다");
		Save_Info(city, player,Turn);
		exit(0);
	}
	return Select;
}
void Load_Info(City* city, Player* player,int* Turn){
	int i, j,k;
	char Buff[100];
	FILE* fo = fopen("Broo_Save.txt", "r");
	for (i = 0; i < 2; i++){
		fscanf(fo, "%s", Buff);
		player[i].Block = atoi(Buff);
		fscanf(fo, "%s", Buff);
		player[i].Give_Up = atoi(Buff);
		fscanf(fo, "%s", Buff);
		player[i].Loc = atoi(Buff);
		fscanf(fo, "%s", Buff);
		player[i].Money = atoi(Buff);
		fscanf(fo, "%s", Buff);
		player[i].Retry = atoi(Buff);
		fscanf(fo, "%s", Buff);
		player[i].Turn_Count = atoi(Buff);
	}
	for (i = 0; i < 30; i++){
		fscanf(fo, "%s", Buff);
		strcpy(city[i].Name, Buff);
		fscanf(fo, "%s", Buff);
		city[i].LT.X = atoi(Buff);
		fscanf(fo,"%s", Buff);
		city[i].LT.Y = atoi(Buff);
		fscanf(fo,"%s", Buff);
		k = atoi(Buff);
		if (k == 0)
			city[i].Owner = NULL;
		else if (k == 1)
			city[i].Owner = &player[0];
		else if (k == 2)
			city[i].Owner = &player[1];

		if (strcmp(city[i].Name, "출발지점") == 0)
			city[i].Special = Start_Func;
		else if (strcmp(city[i].Name, "황금열쇠") == 0)
			city[i].Special = Gold_Key_Func;
		else if (strcmp(city[i].Name, "MT지역") == 0)
			city[i].Special = MT_Func;
		else if (strcmp(city[i].Name, "셔틀버스") == 0)
			city[i].Special = ShuttleBus_Func;
		else if (strcmp(city[i].Name, "대학축제") == 0)
			city[i].Special = Festival_Func;
		else{
			city[i].Special = NULL;
			fscanf(fo, "%s", Buff);
			city[i].level = atoi(Buff);
			for (j = 0; j < 3; j++){
				fscanf(fo, "%s", Buff);
				city[i].Price[j]= atoi(Buff);
			}
			for (j = 0; j < 3; j++){
				fscanf(fo, "%s", Buff);
				city[i].Fine[j] = atoi(Buff);
			}
		}
	}
	fscanf(fo, "%d", Turn);
	fclose(fo);
}
void Save_Info(City* city, Player* player,int Turn){
	int i,j;
	char Buff[100];
	FILE* fo = fopen("Broo_Save.txt", "w");
	for (i = 0; i < 2; i++){
		itoa(player[i].Block, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(player[i].Give_Up, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(player[i].Loc, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(player[i].Money, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(player[i].Retry, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(player[i].Turn_Count, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, "\n");
	}
	for (i = 0; i < 30; i++){
		fprintf(fo, city[i].Name);
		fprintf(fo, " ");
		itoa(city[i].LT.X, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		itoa(city[i].LT.Y, Buff, 10);
		fprintf(fo, Buff);
		fprintf(fo, " ");
		if (city[i].Owner == NULL)
			fprintf(fo, "0 ");
		else if (city[i].Owner == &player[0])
			fprintf(fo, "1 ");
		else if (city[i].Owner == &player[1])
			fprintf(fo, "2 ");
		if (city[i].Special == NULL){
			itoa(city[i].level, Buff, 10);
			fprintf(fo, Buff);
			fprintf(fo, " ");
			for (j = 0; j < 3; j++){
				itoa(city[i].Price[j], Buff, 10);
				fprintf(fo, Buff);
				fprintf(fo, " ");
			}
			for (j = 0; j < 3; j++){
				itoa(city[i].Fine[j], Buff, 10);
				fprintf(fo, Buff);
				fprintf(fo, " ");
			}
		}
		
		fprintf(fo, "\n");
	}
	fprintf(fo, "%d", Turn);
	fclose(fo);
}
// 주요  게임 실행 함수
void Play_Game(int Mode){
	City city[CITY_NUM];
	int Turn, Choose, i;
	char Winner[100];
	Player player[2];
	Print_Base_Board();
	if (Mode == 1){
	//플레이어 초기화
	for (i = 0; i < 2; i++)
		Init_Player(player, &city, i);
	//도시 정보 초기화
	Init_City(city, CITY_NUM);
	Turn = 1;
	}
	else if (Mode == 2){
		Load_Info(city, player,&Turn);
		BG_Upgrade(city, player);
		CHANGE_TURN(Turn, 2);
	}
	//기본 베이스 보드 출력 ( 선 )

	do{
		// 주사위 같은 수에 의한 추가 턴
		if (player[Turn].Retry != 1)
			CHANGE_TURN(Turn, 2);
		else
			player[Turn].Retry = 0;
		Color_Change(Turn);
		if (player[Turn].Block == 0){
			//변화된 내용을 출력
			BG_Upgrade(city, player);
			// 메뉴 출력
			Print_Menu(player, city, Turn);
			// 플레이어가 파산을 선택 시 게임 종료
			// 플레이어가 주사위를 굴렸을 경우
			if (!player[Turn].Give_Up){
				if (city[player[Turn].Loc].Special != NULL)
					city[player[Turn].Loc].Special(city, player, Turn);
				// 그 땅 주인을 물음 없을 시 구매   있을 시 통행료 납부
				else if (city[player[Turn].Loc].Owner == NONE)
					Buy_City(city, player, Turn);
				else if (city[player[Turn].Loc].Owner != &player[Turn])
					Pay_Fine(city, player, Turn);
			}
		}
		//MT지역 턴을 1씩 감소 
		else{
			char Tmp[100] = " 술에서 벗어 나지 못하고 있습니다. 남은 턴";
			char Buff[100];
			itoa(--(player[Turn].Block), Buff, 10);
			strcat(Tmp, Buff);
			Board_Clear();
			gotoPrint(45, 15, Tmp);
			getch();
		}
		Board_Clear();
		BG_Upgrade(city, player);
		//패배조건 확인
	} while (Quiet(city, player, &Turn, player[Turn].Give_Up) == PASS);
	Board_Clear();
	if (Turn == 0)
		strcpy(Winner, "플레이어 1승리");
	else if (Turn == 1)
		strcpy(Winner, "플레이어 2승리");
	gotoPrint(45, 15, Winner);
}