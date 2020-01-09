#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
	int m = 3, n = 10;
	Matrix M(m, n);

	cout << "Matrix M:\n";
	cout << M << endl;

	M += 1.0;
	cout << "Matrix M :\n";
	cout << M << endl;

	cout << "Matrix M+M :\n";
	cout << M+M << endl;

	cout << "Matrix M+M+M :\n";
	cout << M+M+M << endl;

	cout << "End of program." << endl;
	return 0;
}