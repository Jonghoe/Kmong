#include<iostream>
using namespace std;
class A{
public:
	int b;
	A() :b(0){}
};
int main(){
	const A a;
	cout << a.b << endl;
}