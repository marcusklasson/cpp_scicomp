#include <iostream>
#include <cmath>

#include "matrix.hpp"

using namespace std;

#include "r8lib.h" // has to be included after namespace std
#include "r8mat_expm1.h" 

Matrix::Matrix(unsigned int m) {
	mRows = m;
	mCols = m;

	matrix.reserve(mRows);
	for (unsigned int i = 0; i != mRows; ++i) {
		vector<double> col(mCols, 0.0);
		matrix.push_back(col);
	}
}

Matrix::Matrix(const Matrix& B) {
	mRows = B.mRows;
	mCols = B.mCols;

	matrix.reserve(mRows);
	for (unsigned int i = 0; i != mRows; ++i) {
		matrix.push_back(B.matrix[i]);
	}
}

Matrix& Matrix::operator=(const Matrix& B) {
	// Todo: Should be possible to execute if A and B have different sizes!  
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			matrix[i][j] = B.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& B) {
	// Todo: Check if A and B are of same size, if not return error!
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

Matrix& Matrix::operator*(double x) {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			this->matrix[i][j] = x * this->matrix[i][j];
		}
	}
	return *this;	
}
/*
Matrix Matrix::operator*(Matrix& B) {
	Matrix result(this->mRows);
	double temp;
	vector<double> matrixRow;
	for (unsigned int i = 0; i != mRows; ++i) {
		matrixRow = this->matrix[i];
		for (unsigned int j = 0; j != B.mCols; ++j) {
			temp = 0.0;
			for (unsigned int k = 0; k != mRows; ++k) {
				temp += matrixRow[k] * B.matrix[k][j];
				//temp += matrix[i][k] * B.matrix[k][i];
			}
			result.matrix[i][j] = temp;
		}
	}
	return result;
}

Matrix Matrix::transpose() {
	Matrix transposed(this->mRows);
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			transposed.matrix[j][i] = this->matrix[i][j];
		}
	}
	return transposed;
}

double Matrix::trace() {
	double trace = 0.0;
	for (unsigned int i = 0; i != this->mRows; ++i) {
		trace += this->matrix[i][i];
	}
	return trace;
}
*/
double Matrix::normFrobenius() {
	double result = 0.0;
	for (unsigned int i = 0; i != this->mRows; ++i) {
		for (unsigned int j = 0; j != this->mRows; ++j) {
			result += (abs(this->matrix[i][j]) * abs(this->matrix[i][j]) );
		}
	}
	/*
	double trace = 0.0;
	Matrix trA = (*this).transpose();
	trA.printMatrix();
	Matrix trAA = trA * (*this);
	trAA.printMatrix();
	*/
	return result;
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

void Matrix::identity() {
	for (unsigned int i = 0; i != mRows; ++i) {
		for (unsigned int j = 0; j != mCols; ++j) {
			if (i == j) {
				matrix[i][j] = 1.0;	
			} else {
				matrix[i][j] = 0.0;
			}
		}
	}
}

Matrix Matrix::matrixExponential(double t, double tol) {
	int niter = 0;
	double t1, pre;
	// Create identity matrix as result for k = 0
	Matrix result(this->mRows);
	result.identity();
	Matrix temp = result;
	result.printMatrix();

	t1 = abs(t);
	pre = 0.0;
	while (abs(result.normFrobenius() - pre) > tol) {
		++niter;
		if (niter > 1000) {
			cout << "No convergence! Returning current matrix exponential..." << endl;
			return result;
		}
		pre = result.normFrobenius();
		cout << "previous norm: " << pre << endl;
		temp *= (*this);  
		temp = temp * (t1/niter);
		result += temp;
	}
	/*
	if (t < 0) {
		return 1/sum;
	} */

	return result; 
}

int main() {
	cout << "Create matrix from own class" << endl;
	unsigned int m = 3;
	Matrix A(m);
	A.fillMatrix(1);
	//A.identity();
	/*
	Matrix B(m);
	B.fillMatrix(3);
	matrix.printMatrix();
	B.printMatrix();

	matrix *= B; // Matrix multiplication!
	matrix.printMatrix();

	Matrix C(B);
	C.printMatrix();
	*/
	cout << "Matrix exponential from provided routine r8mat_lib: \n";
	int n = 3;
	double array[9] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

	cout << "L2-Norm of matrix: " << r8mat_norm_l2(n, n, array) << "\n";

	double* result = r8mat_expm1(n, array);
	r8mat_print(n, n, result, "Cool matrix");

	Matrix expA = A.matrixExponential();
	expA.printMatrix();

	//cout << "Frobenius norm: \n";
	//double norm = I.normFrobenius();

	return 0;
}