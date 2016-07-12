#include<iostream>
using namespace std;
template<class T>
class Queue
{
private:
	T data[5]; // �ѹ��� �ִ� 5���� ���Ҹ� ����.
	int head; // ���� ó���� �� ������ �ε���
	int tail; // ���� ���Ұ� �� �ε���
	int size; //���� ����

public:
	Queue() // ������
	{
		// head�� tail�� 0���� �ʱ�ȭ
		head = 0;
		tail = 0;
		// ���Ұ����� 0���� �ʱ�ȭ
		size = 0;
		
	}
	T popFront()
	{
		if (isEmpty())
			return -1;
		// result�� head �� ��ġ�� ���Ҹ� ����
		int result;
		result = data[head];
		// head 1 ����, head�� 4�� ��� 5�� �������������Ƿ� 0�� �ȴ�(����ť) 
		head = (head + 1) % 5;
		// ���Ұ��� 1 ����
		size--;
		// ����
		return result;
	}

	void pushBack(T val)
	{
		data[tail] = val; // data[tail]�� ����(val)�� ����
		tail = (tail+1) % 5; // tail 1 ����, tail�� 4�� ��� 5�� �������� �����Ƿ� 0�� �ȴ�(����ť)
		size++; // ���Ұ��� 1 ����
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