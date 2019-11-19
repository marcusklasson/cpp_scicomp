#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
	cout << "Create matrix from own class" << endl;
	unsigned int m = 3;
	Matrix matrix(m);
	matrix.fillMatrix(1);
	Matrix B(m);
	B.fillMatrix(3);
	matrix.printMatrix();
	B.printMatrix();

	matrix *= B; // Matrix multiplication!
	matrix.printMatrix();

	Matrix C(B);
	C.printMatrix();
	/*
	matrix += B;
	matrix.printMatrix();

	matrix += matrix;
	matrix.printMatrix();

	matrix = B;
	matrix.printMatrix();	
	*/
	return 0;
}