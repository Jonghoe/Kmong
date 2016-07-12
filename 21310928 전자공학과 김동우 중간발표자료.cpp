#include <iostream>
#include <cstring>
#include <cstdlib>         // 표준 C 라이브러리 헤더 <stdlib.h>를 포함하고 std 네임스페이스에 연결된 이름을 추가합니다. 
using namespace std;

class DGB {				// Dongwoo 제 영문 이름을 따서 DGB (Dongwoobank) 라고 지었습니다. 
private:
	int AccountNumber;		//계좌 번호
	string Customer;	    //고객 이름
public:
	int Balance;            //고객 잔액
	DGB();					// 생성자
	int getAccountNumber();
	int getBalance(); 
	string getCustomer();
	void showDGB() {
		cout << "안녕하세요 DGB 입니다.";
		cout << "계좌번호 : " << AccountNumber;
		cout << "고객이름 : " << Customer.size();
		cout << "잔    액 : " << Balance;
	}
	~DGB(); // 소멸자
}; //5월 22일 일요일 , 18시 42분 , 작성자 : 김동우

class Deposit :public DGB {				// 입금 클래스
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
	void getDeposit(int DGBmoney);			// 5월 23일 월요일 , 20시 17분 , 작성자 : 김동우

	
	void showDeposit() {
		cout << DGBCustomer.size() << "의 정보는 무엇보다 가장 소중하게 생각합니다.";
		cout << "계좌번호는 " << DGBNumber << " 입니다." << endl;
		cout << "금액 : " << DGBMoney << " 이 입금 되었습니다." << endl;
	}
	~Deposit();
}; // 5월 24일 화요일 , 14시 22분 , 작성자 : 김동우

class Withdraw :public DGB {				// 출금 클래스
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
		cout << DGBCustomer << "의 정보는 무엇보다 가장 소중하게 생각합니다.";
		cout << "계좌번호는 " << DGBNumber << " 입니다." << endl;
		cout << "금액 : " << DGBMoney << " 이 출금 되었습니다." << endl;
	}
}; // 5월 25일 수요일 , 21시 07분 , 작성자 : 김동우

class Account {							//계좌 정보 클래스
private:
	int AccountNumber;		//계좌 번호
	int Balance;			//고객 잔액
	string Customer;		//고객 이름
	string Address;			//고객 주소
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
	cout << "계좌번호 : " << AccountNumber << " 입니다.";
	cout << "고객이름 : " << Customer.size() << " 입니다.";
	cout << "고객주소 : " << Address.size() << " 입니다.";
	cout << "예 금 액 : " << Balance << " 입니다.";
} // 5월 26일 목요일, 22시 42분, 작성자 : 김동우

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
			cout << "입금액을 입력하세요. ";
			cin >> Dmoney;
			account1.getDeposit(Dmoney);
			cout << " 잔액은 " << account1.getBalance() << "원 입니다." << endl;
		}
		break;

		case '2':
		{
			int Wmoney;
			cout << "출금액을 입력하세요. ";
			cin >> Wmoney;
			account2.getWithdraw(Wmoney);
			cout << " 잔액은 " << account2.getBalance() << "원 입니다." << endl;
		}
		break;
		case '3':
		{
			cout << " 잔액은 " << account.getBalance() << "원 입니다." << endl;
		}
		break;
		case '4':
		{
			cout << "프로그램을 종료합니다." << endl;
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
	cout << " DGB 에 오신걸 환영합니다";
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	cout << " 1. 입    금 " << endl;
	cout << " 2. 출    금 " << endl;
	cout << " 3. 잔액조회 " << endl;
	cout << " 4. 프로그램종료" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	cout << "오늘도 좋은하루되세요~" << endl;
	cin >> menu;

	return menu;
} // 5월 29일 일요일 23시 49분 작성자 : 김동우
