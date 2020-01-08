#include <iostream>

using namespace std;

void change(int val, int& ref, int *ptr) {
	val = 1;
	ref = 1;
	*ptr = 1;
}

int main() {
	int i = 0, j = 0, k = 0;
	cout << i << j << k << " --> ";
	change(i,j,&k);
	cout << i << j << k << endl;
}