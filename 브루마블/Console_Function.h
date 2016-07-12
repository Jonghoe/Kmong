#ifndef CONSOLE_H
#define CONSOLE_H
#include"Broo_Type.h"
//칼러 변경
void setcolor(int color, int bgcolor);
//x,y로 커서변경
void gotoxy(int x, int y);
//x,y위치에 m 출력
void gotoPrint(int x, int y, char *m);
//키보드눌려질때까지 대기 하여 값을 받음 (한문자)
int Key_Push();
//출력판 지우기
void Board_Clear();
//인트형을 문자형 ( 만원단위로 ) 바꿔주는 함수
void iToS(int INT, char* string);
//텍스트 칼러를 Turn에 맞추어 변경
void Color_Change(int Turn);
//한줄 지우기
void Line_Claer(int y);
//기본 선그리기
void Print_Base_Board();
//배경그림 업데이트
void BG_Upgrade(City* city, Player* player);
//메뉴 출력
void Print_Menu(Player* player, City* city, int Turn);
//말 그리기
void Piece_Draw(City* city, Player* player, int Turn);
//말 지우기
void Piece_Clear(City* city, Player* player, int Turn);
//건물 그리기
void Building_Draw(City* city, Player* player, int Turn);
//건물 지우기
void Building_Clear(City* city, Player* player, int Turn);
//시작화면 출력
void Start_Screen(int* Type);
#endif