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
	//���� ��ǥ��
	COORD LT;	
	// ���� �̸�
	char Name[100];
	// ������ �ǹ� �ܰ�
	int level;
	// �ǹ� ����
	Player* Owner;
	//������ �ǹ� ����
	int Price[3];
	//������ �ܰ躰 �����
	int Fine[3];
	// Ư�� �����ΰ�츦 ���� ������
	void  (*Special)(City* city,Player* player,int Turn);
};
struct tag_Player{
	//������
	int Money;
	//MT���п� ���� ������
	int Block;
	//���� ��ġ
	int Loc;
	//���� ��ü���� ��ȯ�� Ƚ��
	int Turn_Count;
	//����
	int Give_Up;
	//���� �ֻ��� ������ ���� �߰� ��ȸ�� ���� ��� 1
	int Retry;
};
#endif