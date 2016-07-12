#include<iostream>
using namespace std;
template<class T>
class Queue
{
private:
	T data[5]; // 한번에 최대 5개의 원소를 보관.
	int head; // 제일 처음에 들어간 원소의 인덱스
	int tail; // 다음 원소가 들어갈 인덱스
	int size; //원소 갯수

public:
	Queue() // 생성자
	{
		// head와 tail을 0으로 초기화
		head = 0;
		tail = 0;
		// 원소개수를 0으로 초기화
		size = 0;
		
	}
	T popFront()
	{
		if (isEmpty())
			return -1;
		// result에 head 에 위치한 원소를 저장
		int result;
		result = data[head];
		// head 1 증가, head가 4일 경우 5는 존재하지않으므로 0이 된다(원형큐) 
		head = (head + 1) % 5;
		// 원소갯수 1 감소
		size--;
		// 리턴
		return result;
	}

	void pushBack(T val)
	{
		data[tail] = val; // data[tail]에 원소(val)를 저장
		tail = (tail+1) % 5; // tail 1 증가, tail이 4일 경우 5는 존재하지 않으므로 0이 된다(원형큐)
		size++; // 원소갯수 1 증가
	}
	bool isEmpty()
	{
		return (size == 0);
	}
	bool isFull()
	{
		return (size == 5);
	}
	void display()
	{
		int i;
		if (isEmpty()){
			cout << "Is Empty " << endl;
			return;
		}
		if (head != tail){
			for (i = head; i < 5 && i != tail ; i++)
				cout << data[i] << " ";
			if (i != tail)
				for (i = 0; i < tail; i++)
					cout << data[i] << " ";
		}
		else{
			for (i = head; i < 5; i++)
				cout << data[i] << " ";
			for (i = 0; i < tail; i++)
				cout << data[i] << " ";
		}
		cout << endl;
	}
};

int main(){
	Queue<int> Int_Queue;
	Queue<double> Double_Queue;

	for (int i = 0; i < 5;i++)
		Int_Queue.pushBack(i);
	for (int i = 0; i < 5; i++)
		Double_Queue.pushBack(i+i*0.3);
	cout << "INT" << endl;
	Int_Queue.display();
	cout << "Double" << endl;
	Double_Queue.display();
	cout << endl;
	cout << "INT" << endl;
	for (int i = 0; i < 5; i++){
		Int_Queue.popFront();
		Int_Queue.display();
	}
	cout << "Double" << endl;
	for (int i = 0; i < 5; i++){
		Double_Queue.popFront();
		Double_Queue.display();
	}
}