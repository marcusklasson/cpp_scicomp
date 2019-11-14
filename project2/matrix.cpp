#include "matrix.hpp"

using namespace std;

Matrix::Matrix(unsigned int m) {
	mRows = m;
	mCols = m;

	matrix.reserve(mRows);
	for (unsigned int i = 0; i != mRows; ++i) {
		vector<double> col(mCols, 0.0);
		matrix.push_back(col);
	}
}

Matrix& Matrix::operator=(const Matrix& B) {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			matrix[i][j] = B.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& B) {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			matrix[i][j] += B.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& B) {
	// TODO: Throw error if mRows != B.mCols.
	//if (mRows != B.mCols) {
	//	cerr << "Number of rows in lhs matrix are not the same as number of columns in rhs matrix!";
	//}
	double temp;
	vector<double> matrixRow;
	for (unsigned int i = 0; i != mRows; ++i) {
		matrixRow = matrix[i];
		for (unsigned int j = 0; j != B.mCols; ++j) {
			temp = 0.0;
			for (unsigned int k = 0; k != mRows; ++k) {
				temp += matrixRow[k] * B.matrix[k][j];
				//temp += matrix[i][k] * B.matrix[k][i];
			}
			matrix[i][j] = temp;
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const double x) {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			matrix[i][j] = x * matrix[i][j];
		}
	}
	return *this;	
}

void Matrix::printMatrix() const {
	cout << "Matrix: " << endl;
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}	
	cout << "\n";
}

void Matrix::fillMatrix(double x) {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			matrix[i][j] = x;
		}
	}
}

int main() {
	cout << "Create matrix from own class" << endl;
	unsigned int m = 3;
	Matrix matrix(m);
	matrix.fillMatrix(1);
	Matrix B(m);
	B.fillMatrix(3);
	matrix.printMatrix();
	B.printMatrix();

	matrix *= B;
	matrix.printMatrix();
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