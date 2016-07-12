#include"Broo_Type.h"
#include"Broo_Func.h"
#include"Console_Function.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
//Ȳ�� ������ �Լ�
//���� ���� �̿� �� 6���� ��� �� 
void Start_Func(City* city, Player* player, int Turn){
	Board_Clear();
	gotoPrint(45, 18, "��� �� ���ʽ� (+ 2000000)");
	player[Turn].Money += 2000000;
	player[Turn].Turn_Count++;
	BG_Upgrade(city, player);
	getch();
}
//MT���� �Լ�
void MT_Func(City* city, Player* player, int Turn){
	gotoPrint(45, 15, "MT������ �����Ͽ����ϴ�. 3�ϰ� ���ָ��°� �˴ϴ�. ");
	player[Turn].Block = 2;
	getch();
}
//��Ʋ���� �Լ� 
void ShuttleBus_Func(City* city, Player* player, int Turn){
	// �����̱� �� ���� �̶� ���ؼ� �ѹ��� ����츦 �����ϱ� ���ؼ�
	int Prev = player[Turn].Loc;
	char Buff[100];
	int I;
	Board_Clear();
	gotoPrint(45, 15, "�̵��� ���� ��ȣ�� �Է��� �ֽʽÿ�. ");
	Piece_Clear(city, player, Turn);
	do{
		fflush(stdin);
		Line_Claer(17);
		gotoxy(45, 17);
		scanf("%s", Buff);
		I = atoi(Buff);
	} while (!(48 <= Buff[0] && Buff[0] <= 57) || I >= CITY_NUM);
	player[Turn].Loc = atoi(Buff);
	//�ѹ��� �����
	if (Prev > player[Turn].Loc)
		city[0].Special(city, player, Turn);

	//���� �׸�
	Piece_Draw(city, player, Turn);
	//�� ������ ��ġ���� �� �� ����
	if (city[player[Turn].Loc].Special != NULL)
		city[player[Turn].Loc].Special(city, player, Turn);
	// �� �� ������ ���� ���� �� ����   ���� �� ����� ����
	else if (city[player[Turn].Loc].Owner == NONE)
		Buy_City(city, player, Turn);
	else if (city[player[Turn].Loc].Owner != player)
		Pay_Fine(city, player, Turn);
}
void Festival_Func(City* city, Player* player, int Turn){
	char Buff[100];
	int Val, i;
	Board_Clear();

	gotoPrint(45, 15, "���б� ���� (������ ���� ���� 2��)");
	gotoPrint(45, 16, "���Ͻô� ������ �Է��Ͽ� �ֽʽÿ�.");
	do{
		Line_Claer(17);
		gotoxy(45, 17);
		scanf("%s", Buff);
		Val = atoi(Buff);
	} while (!(49 <= Buff[0] && Buff[0] <= 57) || Val >= CITY_NUM || city[Val].Owner == NULL);
	Board_Clear();
	itoa(Val, Buff, 10);
	strcat(Buff, "������ ���� ���°� �Ǿ����ϴ�.  || ����� * 2");
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
		gotoPrint(45, 18, "���б� ���� (+ 300��)");
		player[Turn].Money += 3000000;
		break;
	case 1:
		gotoPrint(45, 18, "��ϱ� ���� �� (- 150��) ");
		player[Turn].Money -= 1500000;
		break;
	case 2:
		Piece_Clear(city, player, Turn);
		gotoPrint(45, 18, "��� ���� �� ��Ʋ������ �ٷ� �� �� �տ�");
		gotoPrint(45, 18, "(��Ʋ ���� �������� �̵�)");
		player[Turn].Loc = 23;
		city[player[Turn].Loc].Special(city, player, Turn);
		Piece_Draw(city, player, Turn);
		break;
	case 3:
		gotoPrint(45, 18, "�б� �⹰ �ļ� (- 30 ��)");
		player[Turn].Money -= 300000;
		break;
	case 4:
		gotoPrint(45, 18, "����� ���� ���� �� (- 70��)");
		player[Turn].Money -= 700000;
		break;
	case 5:
		Piece_Clear(city, player, Turn);
		gotoPrint(45, 18, "������ MT���� �� 2�ϵ��� �� ���ñ�");
		gotoPrint(45, 18, "(MT�������� �̵�)");
		player[Turn].Loc = 8;
		city[player[Turn].Loc].Special(city, player, Turn);
		Piece_Draw(city, player, Turn);
		break;
	}
	getch();
}
//�÷��̾��� �� �ʱ�ȭ
void Init_Player(Player* Player, City* city, int Turn){
	Player[Turn].Block = 0;
	Player[Turn].Money = 5000000;
	Player[Turn].Turn_Count = 0;
	Player[Turn].Loc = 0;
	Player[Turn].Give_Up = 0;
	Player[Turn].Retry = 0;
}
//������ ���� �ʱ�ȭ ���� ������� ���ؼ� ������ ������ �ִ´�.
//�� Ư���Ѱ��� ���� ex) Ȳ�ݿ���, MT, ���� ����
void Init_City(City* city){
	enum Move { UP, RIGHT, DOWN, LEFT };
	int Dir = LEFT;
	FILE* fo = fopen("BrooMable.txt", "r");
	int Move = 0;
	char Buffer[1024];
	int i = 0, j, M = 0;
	if (fo == NULL)
		return NULL;
	//--------------------ù ��� �� �ʱ�ȭ-----------------------
	strcpy(city[0].Name, "�������");
	city[0].Owner = NONE;
	city[0].LT.X = 114;
	city[0].LT.Y = 37;
	city[0].Special = Start_Func;

	//-----------------------------------------------------------
	for (i = 1; i < CITY_NUM; i++){
		//������ ������ ��ǥ�� ��Ÿ�� ( �ʻ� �׸��� ���ؼ� )
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
		//������ �⺻���� �Է�
		fscanf(fo, "%s", city[i].Name);
		city[i].level = -1;
		city[i].Owner = NONE;
		//Ư������ �Լ� ����
		if (strcmp(city[i].Name, "Ȳ�ݿ���") == 0)
			city[i].Special = Gold_Key_Func;
		else if (strcmp(city[i].Name, "MT����") == 0)
			city[i].Special = MT_Func;
		else if (strcmp(city[i].Name, "��Ʋ����") == 0)
			city[i].Special = ShuttleBus_Func;
		else if (strcmp(city[i].Name, "��������") == 0)
			city[i].Special = Festival_Func;
		// �� �� ���� ���� ���� ����
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
		//���� ����
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
			���� ���  (���� ���� )
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
			���� ���  (���� ���� )
			*/
			if (Owner1 == 6 || Owner2 == 6)
				return WIN;
		}
		Loc = Loc + j;
	}
	return PASS;
}

//���� ����
void Buy_City(City* city, Player* player, int Turn){
	int Select;
	char Buff[100];
	char Result[100] = "���Ű� �Ϸ� �Ǿ����ϴ�. - ";
	//�÷��̾��� ���� ���� ���� ������ ���� ��� �׳� ������
	if (city[player[Turn].Loc].Price[0]>player[Turn].Money)
		return;
	Board_Clear();
	gotoPrint(45, 15, "���ø� ���� �Ͻðڽ��ϱ� ? �� : 1 // ��� : 0");
	Print_City_Info(45, 16, &city[player[Turn].Loc]);
	Select = Key_Push();
	Board_Clear();
	if (Select == 0){
		gotoPrint(45, 23, "���Ű� ��� �Ǿ����ϴ�");
		getch();
		return;
	}
	//���ñ��� ����
	if (Select == 1)
		do{
			int Val;
			gotoPrint(45, 15, "�� �ܰ踦 ���� �Ͻðڽ��ϱ� ? //��� : 0");
			Select = Key_Push();
			Board_Clear();
			if (Select == 0){
				gotoPrint(45, 15, "���Ű� ��� �Ǿ����ϴ�");
				getch();
				return;
			}
			//��������� �� Ƚ���� ���缭 �ǹ� ���� ����
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
			//�ǹ� ���������� ��� ���
			else{
				gotoPrint(45, 15, "���Ű� �Ұ��� �մϴ�.");
				getch();
			}
		} while (1);
}

//���� �Ǹ� �Լ�
void Sell_City(Player* player, City* city, int Turn){
	int i = 0,Line;
	int Select = 0;
	char Buff[100];
	int Val;
	//�Ǹ��� ���� ����
	while (1){
		Line = 16;
		Board_Clear();
		Color_Change(Turn);
		gotoPrint(45, 15, "�Ǹ��Ͻ� ���ø� �����Ͽ� �ֽʽÿ�. �Ǹ� ����  : 0");
		for (i = 0; i < CITY_NUM; i++) 
			if ((city)[i].Owner == &player[Turn]){
				char Price[100];
				char Tmp[100];
				strcpy(Price, "�ǸŰ� : ");
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
			gotoPrint(45, ++Line, "�ǸŰ� �Ϸ� �Ǿ����ϴ�.");
			getch();
			Line_Claer(Line);
			return;
		}
		//�ڱ��� ���� �ƴѰ��
		else if (city[Val].Owner != &player[Turn]){
			gotoPrint(45, ++Line, "����� ���� �ƴմϴ�.");
			getch();
			Line_Claer(Line);
		}
		//�ڱ��� ���� ��� ���� �Ǹ�
		else{
			city[Val].Owner = NONE;
			player[Turn].Money += city[Val].Price[city[Val].level];
			city[Val].level = -1;
			Building_Clear(&city[Val], player, Turn);
			gotoPrint(45, ++Line, "�Ǹſ� �����Ͽ����ϴ�.");
			getch();
			Line_Claer(Line);
			BG_Upgrade(city, player);
		}
	}
}
//����� ���� 
void Pay_Fine(City* city, Player* player, int Turn){
	Board_Clear();
	//����Ẹ�� ���� ���� ���� ��� �� �Ǹ� 
	if (city[player[Turn].Loc].Fine[city[player[Turn].Loc].level] > player[Turn].Money){
		gotoPrint(45, 15, "�ݾ��� �����մϴ�  ���� �Ⱦ� �ֽʽÿ�");
		getch();
		Board_Clear();
		Sell_City(player, city, Turn);
		//�� �Ǹ� �Ŀ��� ���� ������ ��� �Ļ����� ����
		if (city[player[Turn].Loc].Fine[city[player[Turn].Loc].level] > player[Turn].Money)
			player[Turn].Give_Up = PASAN;
	}
	//�÷��̾ �Ļ��� �ƴ� ��� ����Ḧ �����ϰ� ���ø� �� �� ���θ� ����
	if (player[Turn].Give_Up != PASAN){
		char Fine[100];
		char Message[100];
		iToS(city[player[Turn].Loc].Fine[city[player[Turn].Loc].level], Fine);
		player[Turn].Money -= city[player[Turn].Loc].Fine[city[player[Turn].Loc].level];
		city[player[Turn].Loc].Owner->Money += city[player[Turn].Loc].Fine[city[player[Turn].Loc].level];
		BG_Upgrade(city, player);
		Color_Change(Turn);
		strcpy(Message, "����Ḧ �����Ͽ����ϴ� - ");
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
	char Tmp1[100] = "ù ���� �ֻ��� �� : ";
	char Tmp2[100] = "�� ���� �ֻ��� �� : ";
	srand(time(NULL));
	I = (rand() % 25 * 125) % 6 + 1;
	//��Ʈ���� ���ڿ��� ���� �� ���
	itoa(I, Buff, 10);
	strcat(Tmp1, Buff);
	gotoPrint(45, 15, Tmp1);
	//
	Ret_V += I;
	I = (rand() % 25 * 125) % 6 + 1;
	//��Ʈ���� ���ڿ��� ���� �� ���
	itoa(I, Buff, 10);
	strcat(Tmp2, Buff);
	gotoPrint(45, 16, Tmp2);
	//
	//������ ���� ���� �ֻ����� ���� ���
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
		gotoPrint(45, 15, "�÷��̾ �Ļ��� ���� �ϼ̽��ϴ� .");
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
		gotoPrint(45, 15, "���� ��ȣ�� �Է� �Ͻʽÿ� ");
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
		gotoPrint(45, 15, "�����͸� �����ϰ� �����մϴ�");
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

		if (strcmp(city[i].Name, "�������") == 0)
			city[i].Special = Start_Func;
		else if (strcmp(city[i].Name, "Ȳ�ݿ���") == 0)
			city[i].Special = Gold_Key_Func;
		else if (strcmp(city[i].Name, "MT����") == 0)
			city[i].Special = MT_Func;
		else if (strcmp(city[i].Name, "��Ʋ����") == 0)
			city[i].Special = ShuttleBus_Func;
		else if (strcmp(city[i].Name, "��������") == 0)
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
// �ֿ�  ���� ���� �Լ�
void Play_Game(int Mode){
	City city[CITY_NUM];
	int Turn, Choose, i;
	char Winner[100];
	Player player[2];
	Print_Base_Board();
	if (Mode == 1){
	//�÷��̾� �ʱ�ȭ
	for (i = 0; i < 2; i++)
		Init_Player(player, &city, i);
	//���� ���� �ʱ�ȭ
	Init_City(city, CITY_NUM);
	Turn = 1;
	}
	else if (Mode == 2){
		Load_Info(city, player,&Turn);
		BG_Upgrade(city, player);
		CHANGE_TURN(Turn, 2);
	}
	//�⺻ ���̽� ���� ��� ( �� )

	do{
		// �ֻ��� ���� ���� ���� �߰� ��
		if (player[Turn].Retry != 1)
			CHANGE_TURN(Turn, 2);
		else
			player[Turn].Retry = 0;
		Color_Change(Turn);
		if (player[Turn].Block == 0){
			//��ȭ�� ������ ���
			BG_Upgrade(city, player);
			// �޴� ���
			Print_Menu(player, city, Turn);
			// �÷��̾ �Ļ��� ���� �� ���� ����
			// �÷��̾ �ֻ����� ������ ���
			if (!player[Turn].Give_Up){
				if (city[player[Turn].Loc].Special != NULL)
					city[player[Turn].Loc].Special(city, player, Turn);
				// �� �� ������ ���� ���� �� ����   ���� �� ����� ����
				else if (city[player[Turn].Loc].Owner == NONE)
					Buy_City(city, player, Turn);
				else if (city[player[Turn].Loc].Owner != &player[Turn])
					Pay_Fine(city, player, Turn);
			}
		}
		//MT���� ���� 1�� ���� 
		else{
			char Tmp[100] = " ������ ���� ���� ���ϰ� �ֽ��ϴ�. ���� ��";
			char Buff[100];
			itoa(--(player[Turn].Block), Buff, 10);
			strcat(Tmp, Buff);
			Board_Clear();
			gotoPrint(45, 15, Tmp);
			getch();
		}
		Board_Clear();
		BG_Upgrade(city, player);
		//�й����� Ȯ��
	} while (Quiet(city, player, &Turn, player[Turn].Give_Up) == PASS);
	Board_Clear();
	if (Turn == 0)
		strcpy(Winner, "�÷��̾� 1�¸�");
	else if (Turn == 1)
		strcpy(Winner, "�÷��̾� 2�¸�");
	gotoPrint(45, 15, Winner);
}