#include <iostream>

using namespace std;

int main() {
	int a = 1, *p, *q;
	p = &a;
	q = p;
	*q = 2;
	cout << *p << *q << endl;

	//cout << a << endl; 
}