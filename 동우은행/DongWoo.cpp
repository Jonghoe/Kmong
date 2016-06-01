#include<iostream>
#include<conio.h>
#include<vector>
#include<string>
using namespace std;
typedef class InstallmentSaveBankBook ISBB;
string Random_Numlist(int S){
	string tmp;
	tmp.append(to_string(S));
	for (int i = 0; i < 2; i++)
		tmp.append(to_string(rand() % 5));
	for (int i = 0; i < 3; i++)
		tmp.append(to_string(rand() % 10));
	for (int i = 0; i < 2; i++)
		tmp.append(to_string((rand() % 5) + 5));
	return tmp;
}
class Deposit;
class Withdraw;
enum BankBookType{ PAD=1, IS=2 };

//통장 클래스
class BankBook{
	friend class Withdraw;
	friend class Deposit;
protected:
	BankBookType type;
	double Rate;
	int Money;
	string Account;
	string User_Name;
public:

	BankBook();
	BankBook(int _M, string& User,int S){
		Rate = 0.5;
		Money = _M; User_Name = User; Account = Random_Numlist(S);
	}
	void showInfo(){
		string Type = type == PAD ? "입출금" : "적금";
		cout << "사용자 명 : " << User_Name << endl;
		cout << "통장의 계좌 번호 : " << Account << endl;
		cout << "통장 잔고 : " << Money << " 이자율 : " << Rate << endl;
		cout << "통장의 종류 : " << Type << endl;
	}
	BankBookType GetType(){ return type; }
	int GetMoney(){ return Money; }
	string GetUser_Name(){ return User_Name; }
	string GetAccount(){ return Account; }
	double GetRate(){ return Rate; }
	int operator +(int Add_Money){ return Money + Add_Money; }
	int operator -(int Dec_Money){
		if (this->Money - Dec_Money < 0)return -1;
		else return this->Money - Dec_Money;
	}
};
ostream& operator<<(ostream& o, BankBook& B){ 
	
	string Type = B.GetType() == PAD ? "입출금" : "적금";
	o << "사용자 명 : " << B.GetUser_Name() << endl;
	o << "통장의 계좌 번호 : " << B.GetAccount() << endl;
	o << "통장 잔고 : " << B.GetMoney()<< " 이자율 : " << B.GetRate()<< endl;
	o << "통장의 종류 : " << Type << endl;
	return o;
}

//입출금 통장 클래스
class PADBankBook :public BankBook{
public:
	PADBankBook();
	PADBankBook(int _M, string&User, int S) :BankBook(_M, User, S){ type = PAD; }
};
//적금 통장 클래스
class InstallmentSaveBankBook :public BankBook{
private:
	int Mangi;
public:
	ISBB();
	ISBB(int _M, string&User, int Man, int _Rate,int S) :BankBook(_M, User,S)
	{
		type = IS;
		Rate = _Rate;
		Mangi = Man;
	}
};
class Withdraw{
	
public:
	void Behavior(int Num, BankBook& book){
		if (book - Num < 0)
			throw "Lack";
		else
			book.Money = book - Num;
	}
};
class Deposit {
public:
	void Behavior(int Num, BankBook& book){ book.Money = (book + Num); }
};

class Bank{
private:
	size_t Max_Num;
	Deposit Dp;
	Withdraw Wd;
	string Bank_Name;
	vector<BankBook*> List_BankBook[10];
	// vector 안에서 비어있는 공간을 찾아서 그 주소 값을 반환
	BankBook** Find_Blank(int& S){
		int i;
		S = rand() % 10;
		
		for (i = 0; i<List_BankBook[S].size()&& List_BankBook[S][i] != NULL; i++);
		if (i > Max_Num)
			return NULL;
		if (i == List_BankBook[S].size())
			List_BankBook[S].push_back(NULL);
		return &List_BankBook[S][i];
	}
	// 일치하는 통장이있는지 찾아서 반환
	BankBook** Find_BankBook(string Num = "0" ){
		for (int i = 0; i<List_BankBook[Num[0] - 48].size() && List_BankBook[Num[0] - 48][i] != NULL; i++){
			if (List_BankBook[Num[0] - 48][i]->GetAccount() == Num)
				return &List_BankBook[Num[0] - 48][i];
		}
		return NULL;
	}
	// 일치하는 통장을 찾아서 삭제시킴
	bool Delete_BankBook(string&Name,string& Account){
		BankBook** Tmp;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL)
			return false;
		else{
			delete *Tmp;
			*Tmp = NULL;
			return true;
		}
	}
	void Make_BankBook(string&Name,BankBookType type){
		BankBook** Tmp;
		string Type = type == PAD ? "출입금" : "적금";
		// 이미 만든 통장이 있을 경우 한번 물어 본 후 생성
		
		Factory(Name, type);

		return;
		
	}
	// 통장을 만드는 함수
	void Factory(string& Name,BankBookType _type){
		BankBook**Tmp;
		int S = 0;
		//입출금 통장의 경우
		if (_type == PAD){
			Tmp = Find_Blank(S);
			*Tmp = new PADBankBook(0, Name,S);
			cout << S << endl;
			if (*Tmp == NULL)
				cerr << "메모리 동적할당 에러" << endl;

			cout << "통장이 생성 되었습니다." << endl;
			cout << " 통장 계좌 번호는 " << (*Tmp)->GetAccount() << "입니다" << endl;
			return;
		}
		//적금 통장인 경우 만기를 정함
		else if (_type == IS){
			int Select, Mangi;
			double Rate;
			bool Ok = false;
			cout << "적금 만기 기간을 정하 십시오 " << endl;
			cout << "1년(2%) || 3 년(3%) || 5년(5%)" << endl;
			do{
				Ok = true;
				cin >> Select;
				switch (Select)
				{
				case 1:
					Mangi = 1;
					Rate = 0.02;
					break;
				case 3:
					Mangi = 3;
					Rate = 0.03;
					break;
				case 5:
					Mangi = 5;
					Rate = 0.05;
					break;
				default:
					cout << "입력을 잘못하셨습니다. 다시 입력해주십시오" << endl;
					Ok = false;
					break;
				}
			} while (!Ok);
			Tmp = Find_Blank(S);
			(*Tmp) = new ISBB(0, Name, Mangi, Rate,S);
			if ((*Tmp) == NULL)
				cerr << "메모리 동적할당 에러" << endl;

			cout << "통장이 생성 되었습니다." << endl;
			cout << " 통장 계좌 번호는 " << (*Tmp)->GetAccount() << "입니다" << endl;
			return;
		}
	}
	
public:
	Bank(){
		Max_Num = 100;
		Bank_Name = "DWB";
	}
	void Show_BankInfo(){ 
		cout<<"안녕하세요 " <<Bank_Name <<"입니다."<<endl;
	}
	void Show_BBKInfo(string& Account){
		BankBook** Tmp;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "일치하는 계좌가 존재하지 않습니다." << endl;
			cout << "거래를 다시 시작하여 주십시오." << endl;
			return;
		}
		cout<<(**Tmp);

	}
	void Admission(string& Name){ 
		int Select;
		cout << "어떤 종류의 통장을 가입하시겠습니까? " << endl;
		cout << "1 : 출입금 통장\t 2 : 적금 통장 \t 3 : 취소" << endl;
		cin >> Select;
		switch (Select)
		{
		case 1:
			Make_BankBook(Name, BankBookType(Select));
			break;
		case 2:
			Make_BankBook(Name, BankBookType(Select));
			break;
		case 3:
			cout << "취소 되었습니다" << endl;
		default:
			break;
		}
	}
	void Check(string&Name, string& Account){
		BankBook** Tmp;
		int DMoney;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "일치하는 계좌가 존재하지 않습니다." << endl;
			cout << "거래를 다시 시작하여 주십시오." << endl;
			return;
		}
		cout << "통장의 잔고는 : " << (*Tmp)->GetMoney() << endl;
	}

	void Deposit(string& Name,string& Account){ 
		BankBook** Tmp;
		int DMoney;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "일치하는 계좌가 존재하지 않습니다." << endl;
			cout << "거래를 다시 시작하여 주십시오." << endl;
			return;
		}
		cout << "입금액을 입력하세요. ";
		cin >> DMoney;
		Dp.Behavior(DMoney, **Tmp);
		cout << DMoney << "원 이 입금 되었습니다" << endl;
		cout << " 잔액은 " << (*Tmp)->GetMoney() << "원 입니다." << endl;
	}
	void Withdraw(string&Name,string&Account){
		BankBook** Tmp;
		int WMoney;
		char B = 'a';
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "일치하는 계좌가 존재하지 않습니다." << endl;
			cout << "거래를 다시 시작하여 주십시오." << endl;
			return;
		}
		cout << "출금액을 입력하세요. ";
		cin >> WMoney;
		try{
			Wd.Behavior(WMoney, **Tmp);
		}
		catch (char* C){
			B = C[0];
			cout << "통장 잔고가 부족합니다" << endl;
		}
		if (B != 'L')
			cout << WMoney << "원 이 출금 되었습니다" << endl;

		cout << " 잔액은 " << (*Tmp)->GetMoney() << "원 입니다." << endl;
	}
	void Terminate(string& Name){
		int Select;
		BankBook**Tmp;
		string Account;
		cout << "해지하실 통장의 계좌번호를 입력 하여 주십시오" << endl;
		cin >> Account;
		if (Delete_BankBook(Name, Account))
			cout << "통장이 해지 되었습니다." << endl;
		else
			cout << "일치하는 통장을 찾을수 없습니다" << endl;
	}
	~Bank(){
		int i;
		for (i = 0; i < 10; i++)
			for (int j = 0; j < List_BankBook[i].size(); j++){
				cout << j << endl;
				delete List_BankBook[i][j];
			}
	}
};
char selectmenu(){
	char menu;
	cout << " DGB 에 오신걸 환영합니다";
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	cout << " 1. 입    금 " << endl;
	cout << " 2. 출    금 " << endl;
	cout << " 3. 잔액조회 " << endl;
	cout << " 4. 통장 정보 확인 " << endl;
	cout << " 5. 계좌 생성" << endl;
	cout << " 6. 계좌 해지" << endl;
	cout << " 7. 프로그램종료" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	cout << "오늘도 좋은하루되세요~" << endl;
	cin >> menu;
	return menu;
}
int main(){
	Bank DGB;
	string account;
	string Name = "DongWoo";
	char ab;
	do {
		switch (ab = selectmenu()) {
		case '1':
		{
			cout << "입금하실 계좌를 입력해주십시오" << endl;
			cin >> account;
			DGB.Deposit(Name,account);
			
		}
		break;

		case '2':
		{
			cout << "출금하실 계좌를 입력해주십시오" << endl;
			cin >> account;
				DGB.Withdraw(Name, account);
			
		}
		break;
		case '3':
		{
			cout << "잔고를 확인 하실 계좌를 입력해주십시오" << endl;
			cin >> account;
			DGB.Check(Name, account);
		}
		break;
		case '4':
		{
			cout << "정보를 확인할 통장의 계좌를 입력해 주십시오" << endl;
			cin >> account;
			DGB.Show_BBKInfo(account);
			break;
		}
		case '5':
		{
			DGB.Admission(Name);
		}
		break;
		case '6':
		{
			DGB.Terminate(Name);
		}
		break;
		case '7':
		{
			cout << "프로그램을 종료합니다." << endl;
		}
		break;
		}
		getch();
		system("cls");
	} while (ab != '7');
	return 0;
}