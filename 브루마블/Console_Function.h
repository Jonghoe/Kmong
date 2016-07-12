#ifndef CONSOLE_H
#define CONSOLE_H
#include"Broo_Type.h"
//Į�� ����
void setcolor(int color, int bgcolor);
//x,y�� Ŀ������
void gotoxy(int x, int y);
//x,y��ġ�� m ���
void gotoPrint(int x, int y, char *m);
//Ű���崭���������� ��� �Ͽ� ���� ���� (�ѹ���)
int Key_Push();
//����� �����
void Board_Clear();
//��Ʈ���� ������ ( ���������� ) �ٲ��ִ� �Լ�
void iToS(int INT, char* string);
//�ؽ�Ʈ Į���� Turn�� ���߾� ����
void Color_Change(int Turn);
//���� �����
void Line_Claer(int y);
//�⺻ ���׸���
void Print_Base_Board();
//���׸� ������Ʈ
void BG_Upgrade(City* city, Player* player);
//�޴� ���
void Print_Menu(Player* player, City* city, int Turn);
//�� �׸���
void Piece_Draw(City* city, Player* player, int Turn);
//�� �����
void Piece_Clear(City* city, Player* player, int Turn);
//�ǹ� �׸���
void Building_Draw(City* city, Player* player, int Turn);
//�ǹ� �����
void Building_Clear(City* city, Player* player, int Turn);
//����ȭ�� ���
void Start_Screen(int* Type);
#endif