#include <iostream>
#include <cstring>
#include <cstdlib>         // ǥ�� C ���̺귯�� ��� <stdlib.h>�� �����ϰ� std ���ӽ����̽��� ����� �̸��� �߰��մϴ�. 
using namespace std;

class DGB {				// Dongwoo �� ���� �̸��� ���� DGB (Dongwoobank) ��� �������ϴ�. 
private:
	int AccountNumber;		//���� ��ȣ
	string Customer;	    //�� �̸�
public:
	int Balance;            //�� �ܾ�
	DGB();					// ������
	int getAccountNumber();
	int getBalance(); 
	string getCustomer();
	void showDGB() {
		cout << "�ȳ��ϼ��� DGB �Դϴ�.";
		cout << "���¹�ȣ : " << AccountNumber;
		cout << "���̸� : " << Customer.size();
		cout << "��    �� : " << Balance;
	}
	~DGB(); // �Ҹ���
}; //5�� 22�� �Ͽ��� , 18�� 42�� , �ۼ��� : �赿��

class Deposit :public DGB {				// �Ա� Ŭ����
private:
	string DGBCustomer;
	int DGBNumber;
	int DGBMoney;	
public:
	Deposit();
	void getDGBCustomer(string DGBC);
	void getDGBNumber(int DGBNumber) {
		this->DGBNumber = DGBNumber;
	}
	void getDeposit(int DGBmoney);			// 5�� 23�� ������ , 20�� 17�� , �ۼ��� : �赿��

	
	void showDeposit() {
		cout << DGBCustomer.size() << "�� ������ �������� ���� �����ϰ� �����մϴ�.";
		cout << "���¹�ȣ�� " << DGBNumber << " �Դϴ�." << endl;
		cout << "�ݾ� : " << DGBMoney << " �� �Ա� �Ǿ����ϴ�." << endl;
	}
	~Deposit();
}; // 5�� 24�� ȭ���� , 14�� 22�� , �ۼ��� : �赿��

class Withdraw :public DGB {				// ��� Ŭ����
	char DGBCustomer;
	int DGBNumber;
	int DGBMoney;
public:
	void getDGBCustomer();
	void getDGBNumber(int DGBNumber) {
		this->DGBNumber = DGBNumber;
	}
	void getWithdraw(int DGBmoney);
	void showWithdraw() {
		cout << DGBCustomer << "�� ������ �������� ���� �����ϰ� �����մϴ�.";
		cout << "���¹�ȣ�� " << DGBNumber << " �Դϴ�." << endl;
		cout << "�ݾ� : " << DGBMoney << " �� ��� �Ǿ����ϴ�." << endl;
	}
}; // 5�� 25�� ������ , 21�� 07�� , �ۼ��� : �赿��

class Account {							//���� ���� Ŭ����
private:
	int AccountNumber;		//���� ��ȣ
	int Balance;			//�� �ܾ�
	string Customer;		//�� �̸�
	string Address;			//�� �ּ�
public:
	Account();
	void setAccountNumber(int DGBN);
	void setBalance(int DGBB);
	void setCustomer(string DGBC);
	string getAddress();
	void showAcoount();
	~Account();
};

int DGB::getAccountNumber() {
	return AccountNumber;
}
int DGB::getBalance() {
	return Balance;
}
string DGB::getCustomer() {
	return Customer;
}
string Account::getAddress() {
	return Address;
}

void Account::setAccountNumber(int DGBN) {
	AccountNumber = DGBN;

}
void Account::setCustomer(string DGBC) {
	Customer = DGBC;
}

void Account::setBalance(int DGBB) {
	Balance = DGBB;
}

void Deposit::getDeposit(int DGBM) {
	Balance += DGBM;
}

void Withdraw::getWithdraw(int DGBM) {
	Balance -= DGBM;
}
void Account::showAcoount() {
	cout << "���¹�ȣ : " << AccountNumber << " �Դϴ�.";
	cout << "���̸� : " << Customer.size() << " �Դϴ�.";
	cout << "���ּ� : " << Address.size() << " �Դϴ�.";
	cout << "�� �� �� : " << Balance << " �Դϴ�.";
} // 5�� 26�� �����, 22�� 42��, �ۼ��� : �赿��

char selectmenu();

int main(int argc, char*argv[]) {
	DGB account;
	Deposit account1;
	Withdraw account2;
	account.getBalance();
	char ab;

	do {
		switch (ab = selectmenu()) {
		case '1':
		{
			int Dmoney;
			cout << "�Աݾ��� �Է��ϼ���. ";
			cin >> Dmoney;
			account1.getDeposit(Dmoney);
			cout << " �ܾ��� " << account1.getBalance() << "�� �Դϴ�." << endl;
		}
		break;

		case '2':
		{
			int Wmoney;
			cout << "��ݾ��� �Է��ϼ���. ";
			cin >> Wmoney;
			account2.getWithdraw(Wmoney);
			cout << " �ܾ��� " << account2.getBalance() << "�� �Դϴ�." << endl;
		}
		break;
		case '3':
		{
			cout << " �ܾ��� " << account.getBalance() << "�� �Դϴ�." << endl;
		}
		break;
		case '4':
		{
			cout << "���α׷��� �����մϴ�." << endl;
		}
		break;
		}
		system("pause");
		system("cls");
	} while (ab != '4');
	return 0;
}

char selectmenu() {
	char menu;
	cout << " DGB �� ���Ű� ȯ���մϴ�";
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << " 1. ��    �� " << endl;
	cout << " 2. ��    �� " << endl;
	cout << " 3. �ܾ���ȸ " << endl;
	cout << " 4. ���α׷�����" << endl;
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	cout << "���õ� �����Ϸ�Ǽ���~" << endl;
	cin >> menu;

	return menu;
} // 5�� 29�� �Ͽ��� 23�� 49�� �ۼ��� : �赿��
