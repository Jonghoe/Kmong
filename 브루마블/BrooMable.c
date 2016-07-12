#include"Broo_Func.h"
#include"Console_Function.h"
int main(){
	int Type;
	Start_Screen(&Type);
	Play_Game(Type);
	gotoxy(0, 41);
	printf("\n");
	getch();
}