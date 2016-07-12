#include<Windows.h>
#ifndef BROO_TYPE_H
#define BROO_TYPE_H
#define ROW 130
#define COL = 30
#define NONE 0
#define WIN 1
#define GG 0
#define PASS 2
#define PASAN 10
#define CITY_NUM 30
#define WAIT_TIME 1000
#define CHANGE_TURN(x,n) (x) = ((x)+1)%(n)
#define PLAYER_1_Color 10
#define PLAYER_2_Color 12
typedef struct tag_City City;
typedef struct tag_Player Player;
typedef struct tag_GoldKey GoldKey;
struct tag_City{
	//맵의 좌표값
	COORD LT;	
	// 도시 이름
	char Name[100];
	// 도시의 건물 단계
	int level;
	// 건물 주인
	Player* Owner;
	//도시의 건물 가격
	int Price[3];
	//도시의 단계별 통행료
	int Fine[3];
	// 특수 지역인경우를 위한 포인터
	void  (*Special)(City* city,Player* player,int Turn);
};
struct tag_Player{
	//소지금
	int Money;
	//MT덕분에 술에 빠진날
	int Block;
	//현재 위치
	int Loc;
	//내가 전체맵을 순환한 횟수
	int Turn_Count;
	//포기
	int Give_Up;
	//같은 주사위 값으로 인해 추가 기회를 얻은 경우 1
	int Retry;
};
#endif