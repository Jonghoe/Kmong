#include"Broo_Type.h"
//Ȳ�ݿ��� �Լ� �� 6��
void Gold_Key_Func(Player* player);
//�÷��̾� �ʱ�ȭ
void Init_Player(Player* Player, City(*city)[28], int turn);
//�������� �ʱ�ȭ
void Init_City(City* city, int n);
//���ε��� Ȯ��
int Line_Monopoly(City* city);
//���� ���� �Լ�
void Buy_City(City* city, Player* player);
//���� �Ǹ� �Լ�
void Sell_City(Player* player, City* city);
//����� �Լ�
void Pay_Fine(City* city, Player* player);
//���� �Ǵ� �Լ�
int Quiet(City* city, Player* player, int Choose);
//�ֻ��� ������
int Roll_The_Dice();
//���� ������ �ֿ��Լ�( main���� )
void Play_Game();
//�� �׸���
void Piece_Draw(City* city, Player* player, int Turn);
//���� ���̺�
void Save_Info(City* city, Player* player,int Turn);
//���� �ε�
void Load_Info(City* city, Player* player,int* Turn);
