#include"Broo_Type.h"
//황금열쇠 함수 총 6개
void Gold_Key_Func(Player* player);
//플레이어 초기화
void Init_Player(Player* Player, City(*city)[28], int turn);
//도시정보 초기화
void Init_City(City* city, int n);
//라인독점 확인
int Line_Monopoly(City* city);
//도시 구매 함수
void Buy_City(City* city, Player* player);
//도시 판매 함수
void Sell_City(Player* player, City* city);
//통행료 함수
void Pay_Fine(City* city, Player* player);
//종료 판단 함수
int Quiet(City* city, Player* player, int Choose);
//주사위 굴리기
int Roll_The_Dice();
//게임 돌리는 주요함수( main역할 )
void Play_Game();
//말 그리기
void Piece_Draw(City* city, Player* player, int Turn);
//파일 세이브
void Save_Info(City* city, Player* player,int Turn);
//파일 로드
void Load_Info(City* city, Player* player,int* Turn);
