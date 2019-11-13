#include <iostream>
#include "matrix.hpp"

using namespace std;

Matrix::Matrix(int m) {
	double matrix[m][m] = {0};
}

void Matrix::printMatrix() const {
	
}


int main() {
	cout << "Create matrix from own class" << endl;
	int m = 2;
	Matrix matrix(m);
	cout << "it worked?" << endl;
}