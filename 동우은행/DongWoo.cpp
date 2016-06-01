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

//���� Ŭ����
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
		string Type = type == PAD ? "�����" : "����";
		cout << "����� �� : " << User_Name << endl;
		cout << "������ ���� ��ȣ : " << Account << endl;
		cout << "���� �ܰ� : " << Money << " ������ : " << Rate << endl;
		cout << "������ ���� : " << Type << endl;
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
	
	string Type = B.GetType() == PAD ? "�����" : "����";
	o << "����� �� : " << B.GetUser_Name() << endl;
	o << "������ ���� ��ȣ : " << B.GetAccount() << endl;
	o << "���� �ܰ� : " << B.GetMoney()<< " ������ : " << B.GetRate()<< endl;
	o << "������ ���� : " << Type << endl;
	return o;
}

//����� ���� Ŭ����
class PADBankBook :public BankBook{
public:
	PADBankBook();
	PADBankBook(int _M, string&User, int S) :BankBook(_M, User, S){ type = PAD; }
};
//���� ���� Ŭ����
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
	// vector �ȿ��� ����ִ� ������ ã�Ƽ� �� �ּ� ���� ��ȯ
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
	// ��ġ�ϴ� �������ִ��� ã�Ƽ� ��ȯ
	BankBook** Find_BankBook(string Num = "0" ){
		for (int i = 0; i<List_BankBook[Num[0] - 48].size() && List_BankBook[Num[0] - 48][i] != NULL; i++){
			if (List_BankBook[Num[0] - 48][i]->GetAccount() == Num)
				return &List_BankBook[Num[0] - 48][i];
		}
		return NULL;
	}
	// ��ġ�ϴ� ������ ã�Ƽ� ������Ŵ
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
		string Type = type == PAD ? "���Ա�" : "����";
		// �̹� ���� ������ ���� ��� �ѹ� ���� �� �� ����
		
		Factory(Name, type);

		return;
		
	}
	// ������ ����� �Լ�
	void Factory(string& Name,BankBookType _type){
		BankBook**Tmp;
		int S = 0;
		//����� ������ ���
		if (_type == PAD){
			Tmp = Find_Blank(S);
			*Tmp = new PADBankBook(0, Name,S);
			cout << S << endl;
			if (*Tmp == NULL)
				cerr << "�޸� �����Ҵ� ����" << endl;

			cout << "������ ���� �Ǿ����ϴ�." << endl;
			cout << " ���� ���� ��ȣ�� " << (*Tmp)->GetAccount() << "�Դϴ�" << endl;
			return;
		}
		//���� ������ ��� ���⸦ ����
		else if (_type == IS){
			int Select, Mangi;
			double Rate;
			bool Ok = false;
			cout << "���� ���� �Ⱓ�� ���� �ʽÿ� " << endl;
			cout << "1��(2%) || 3 ��(3%) || 5��(5%)" << endl;
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
					cout << "�Է��� �߸��ϼ̽��ϴ�. �ٽ� �Է����ֽʽÿ�" << endl;
					Ok = false;
					break;
				}
			} while (!Ok);
			Tmp = Find_Blank(S);
			(*Tmp) = new ISBB(0, Name, Mangi, Rate,S);
			if ((*Tmp) == NULL)
				cerr << "�޸� �����Ҵ� ����" << endl;

			cout << "������ ���� �Ǿ����ϴ�." << endl;
			cout << " ���� ���� ��ȣ�� " << (*Tmp)->GetAccount() << "�Դϴ�" << endl;
			return;
		}
	}
	
public:
	Bank(){
		Max_Num = 100;
		Bank_Name = "DWB";
	}
	void Show_BankInfo(){ 
		cout<<"�ȳ��ϼ��� " <<Bank_Name <<"�Դϴ�."<<endl;
	}
	void Show_BBKInfo(string& Account){
		BankBook** Tmp;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "��ġ�ϴ� ���°� �������� �ʽ��ϴ�." << endl;
			cout << "�ŷ��� �ٽ� �����Ͽ� �ֽʽÿ�." << endl;
			return;
		}
		cout<<(**Tmp);

	}
	void Admission(string& Name){ 
		int Select;
		cout << "� ������ ������ �����Ͻðڽ��ϱ�? " << endl;
		cout << "1 : ���Ա� ����\t 2 : ���� ���� \t 3 : ���" << endl;
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
			cout << "��� �Ǿ����ϴ�" << endl;
		default:
			break;
		}
	}
	void Check(string&Name, string& Account){
		BankBook** Tmp;
		int DMoney;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "��ġ�ϴ� ���°� �������� �ʽ��ϴ�." << endl;
			cout << "�ŷ��� �ٽ� �����Ͽ� �ֽʽÿ�." << endl;
			return;
		}
		cout << "������ �ܰ�� : " << (*Tmp)->GetMoney() << endl;
	}

	void Deposit(string& Name,string& Account){ 
		BankBook** Tmp;
		int DMoney;
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "��ġ�ϴ� ���°� �������� �ʽ��ϴ�." << endl;
			cout << "�ŷ��� �ٽ� �����Ͽ� �ֽʽÿ�." << endl;
			return;
		}
		cout << "�Աݾ��� �Է��ϼ���. ";
		cin >> DMoney;
		Dp.Behavior(DMoney, **Tmp);
		cout << DMoney << "�� �� �Ա� �Ǿ����ϴ�" << endl;
		cout << " �ܾ��� " << (*Tmp)->GetMoney() << "�� �Դϴ�." << endl;
	}
	void Withdraw(string&Name,string&Account){
		BankBook** Tmp;
		int WMoney;
		char B = 'a';
		Tmp = Find_BankBook(Account);
		if (Tmp == NULL){
			cout << "��ġ�ϴ� ���°� �������� �ʽ��ϴ�." << endl;
			cout << "�ŷ��� �ٽ� �����Ͽ� �ֽʽÿ�." << endl;
			return;
		}
		cout << "��ݾ��� �Է��ϼ���. ";
		cin >> WMoney;
		try{
			Wd.Behavior(WMoney, **Tmp);
		}
		catch (char* C){
			B = C[0];
			cout << "���� �ܰ� �����մϴ�" << endl;
		}
		if (B != 'L')
			cout << WMoney << "�� �� ��� �Ǿ����ϴ�" << endl;

		cout << " �ܾ��� " << (*Tmp)->GetMoney() << "�� �Դϴ�." << endl;
	}
	void Terminate(string& Name){
		int Select;
		BankBook**Tmp;
		string Account;
		cout << "�����Ͻ� ������ ���¹�ȣ�� �Է� �Ͽ� �ֽʽÿ�" << endl;
		cin >> Account;
		if (Delete_BankBook(Name, Account))
			cout << "������ ���� �Ǿ����ϴ�." << endl;
		else
			cout << "��ġ�ϴ� ������ ã���� �����ϴ�" << endl;
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
	cout << " DGB �� ���Ű� ȯ���մϴ�";
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << " 1. ��    �� " << endl;
	cout << " 2. ��    �� " << endl;
	cout << " 3. �ܾ���ȸ " << endl;
	cout << " 4. ���� ���� Ȯ�� " << endl;
	cout << " 5. ���� ����" << endl;
	cout << " 6. ���� ����" << endl;
	cout << " 7. ���α׷�����" << endl;
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << "���õ� �����Ϸ�Ǽ���~" << endl;
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
			cout << "�Ա��Ͻ� ���¸� �Է����ֽʽÿ�" << endl;
			cin >> account;
			DGB.Deposit(Name,account);
			
		}
		break;

		case '2':
		{
			cout << "����Ͻ� ���¸� �Է����ֽʽÿ�" << endl;
			cin >> account;
				DGB.Withdraw(Name, account);
			
		}
		break;
		case '3':
		{
			cout << "�ܰ� Ȯ�� �Ͻ� ���¸� �Է����ֽʽÿ�" << endl;
			cin >> account;
			DGB.Check(Name, account);
		}
		break;
		case '4':
		{
			cout << "������ Ȯ���� ������ ���¸� �Է��� �ֽʽÿ�" << endl;
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
			cout << "���α׷��� �����մϴ�." << endl;
		}
		break;
		}
		getch();
		system("cls");
	} while (ab != '7');
	return 0;
}