#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <stdlib.h> 

#include "matrix.hpp"
#include "myMatrixExponential.hpp"

using namespace std;

#include "r8lib.h" // has to be included after namespace std
#include "r8mat_expm1.h" 

Matrix::Matrix(unsigned int m) {
	mRows = m;
	mCols = m;

	matrix.reserve(mRows);
	for (unsigned int i = 0; i < mRows; ++i) {
		vector<double> col(mCols, 0.0);
		matrix.push_back(col);
	}
}

Matrix::Matrix(const Matrix& B) {
	mRows = B.mRows;
	mCols = B.mCols;

	matrix.reserve(mRows);
	for (unsigned int i = 0; i < mRows; ++i) {
		matrix.push_back(B.matrix[i]);
	}
}

//Matrix::Matrix(const char* filename) {
Matrix::Matrix(const string& filename) {
	ifstream infile(filename);

	if (infile) {
		string line;
		double value;

		while (getline(infile, line)) {
			this->matrix.push_back(vector<double>());
			stringstream split(line);
			
			while (split >> value) {
				this->matrix.back().push_back(value);
			}	
		}
		
		mRows = this->matrix.size(); // get rows
		mCols = this->matrix[0].size(); // get columns

		/*
		// Print matrix
		cout << "Print matrix from file: \n" << endl;
		for (unsigned int i = 0; i < mRows; ++i) {
			for (unsigned int j = 0; j < mCols; ++j) {
				cout << this->matrix[i][j] << ' ';
			}
		}
		cout << '\n';
		*/
	}
}

Matrix& Matrix::operator=(const Matrix& B) {
	// Todo: Should be possible to execute if A and B have different sizes!  
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			this->matrix[i][j] = B.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& B) {
	if ((this->mRows != B.getRows()) && (this->mCols != B.getCols()) ) {
		cout << "ERROR! Matrices must have the same size!\n";
		cout << "Exiting program... \n\n";
		exit(EXIT_FAILURE);
	}
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			this->matrix[i][j] += B.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& B) {
	if ((*this).getRows() != B.getCols()) {
		cout << "ERROR! Number of rows in lhs matrix are not the same as number of columns in rhs matrix!\n";
		cout << "Exiting program... \n\n";
		exit(EXIT_FAILURE);
	}
	double temp;
	vector<double> matrixRow;
	for (unsigned int i = 0; i < this->mRows; ++i) {
		matrixRow = matrix[i];
		for (unsigned int j = 0; j < B.getCols(); ++j) {
			temp = 0.0;
			for (unsigned int k = 0; k < this->mRows; ++k) {
				temp += matrixRow[k] * B.matrix[k][j];
				//temp += matrix[i][k] * B.matrix[k][i];
			}
			this->matrix[i][j] = temp;
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const double x) {
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			this->matrix[i][j] = x * this->matrix[i][j];
		}
	}
	return *this;	
}

Matrix& Matrix::operator*(double x) {
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			this->matrix[i][j] = x * this->matrix[i][j];
		}
	}
	return *this;	
}

double Matrix::normFrobenius() {
	double result = 0.0;
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mRows; ++j) {
			result += (abs(this->matrix[i][j]) * abs(this->matrix[i][j]) );
		}
	}
	result = sqrt(result);
	return result;
}

void Matrix::printMatrix() const {
	cout << "Print matrix: \n" << endl;
	/*
	cout << right << setw(5) << "Col:";
	for (int i = 0; i < this->mCols; ++i) {
		cout << setw(10) << i;
	}
	cout << "\n";
	*/
	//cout << right << setw(5) << "Row\n";
	for (unsigned int i = 0; i < this->mRows; ++i) {
		//cout << right << setw(5) << i << ":";
		for (unsigned int j = 0; j < this->mCols; ++j) {
			cout << right << setw(10) << this->matrix[i][j];
		}
		cout << "\n";
	}	
	cout << "\n";
}

void Matrix::fillMatrix(double x) {
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			this->matrix[i][j] = x;
		}
	}
}

void Matrix::identity() {
	for (unsigned int i = 0; i < this->mRows; ++i) {
		for (unsigned int j = 0; j < this->mCols; ++j) {
			if (i == j) {
				this->matrix[i][j] = 1.0;	
			} else {
				this->matrix[i][j] = 0.0;
			}
		}
	}
}
