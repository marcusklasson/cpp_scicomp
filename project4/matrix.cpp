#include <iostream>
#include <cassert> // for assert
#include <stdio.h>
#include "matrix.hpp"

using namespace std;

Matrix::Matrix(int m_, int n_) : m(m_), n(n_), A(nullptr) {
	if (m*n > 0) {
		A = new double[m*n];
		for (int i = 0; i < m*n; ++i) { // fill matrix with zeros
			A[i] = 0.0;
		}
	} 
}

// Copy constructor
Matrix::Matrix(const Matrix& M) {
	std::cout << "inside copy constructor! \n";
	m = M.m;
	n = M.n;
	A = nullptr;

	if (m*n > 0) {
		A = new double[m*n];
		for (int i = 0; i < m*n; ++i) {
			A[i] = M.A[i];
		}
	}
}


Matrix::~Matrix() {
	if (A != nullptr) {
		delete[] A;
	}
}

// Copy assignment operator
Matrix& Matrix::operator=(const Matrix& M) {

	if (this == &M) {
		return *this;
	}
		
	if (m == M.m && n == M.n) {
		for (int i = 0; i < m*n; ++i) {
			A[i] = M.A[i];
		}
	} else {
		delete[] A;
		
		m = M.m;
		n = M.n;
		A = nullptr;	
		if (m*n > 0) {
			A = new double[m*n];
			for (int i = 0; i < m*n; ++i) {
				A[i] = M.A[i];
			}
		}
	}
	return *this;
} 


// Move assignment operator
Matrix &Matrix::operator=(Matrix &&M) noexcept{
    if (this == &M) {
        return *this;
    }
    m = M.m;
    n = M.n;
    A = M.A;
    M.m = 0;
    M.n = 0;
    M.A = nullptr;

    return *this;
}


const Matrix& Matrix::operator+=(const Matrix& M) {
	assert(m == M.m); // Matrix addition requires same size
	assert(n == M.n);
	for (int i = 0; i < m*n; ++i) {
		A[i] += M.A[i];
	}
	return *this;
}

const Matrix& Matrix::operator+=(const double x) {
	if (m*n > 0) {
		for (int i = 0; i < m*n; ++i) {
			A[i] += x;
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& M) const {
	assert(m == M.m); // Matrix addition requires same size
	assert(n == M.n);

	Matrix result(m, n);
	for (int i = 0; i < m*n; ++i) {
		result.A[i] = A[i] + M.A[i];
	}
	return result;
}

const Matrix& Matrix::operator*=(const double c) {
	for (int i = 0; i < m*n; ++i) {
		A[i] = c * A[i];
	}
	return *this;
}

double& Matrix::operator()(int i, int j) const {
	// Elements are stored such that x coordinates are on the row side
	// and y coordinates are on column side
	assert(i >= 0 && i <= m); // m are number of rows
	assert(j >= 0 && j <= n); // n are number of columns
	return A[i+j*m];// return a[j+i*m];

}

void Matrix::printMatrix() const {
	/*
	First point to print is lower left point,
	Then print the whole row, which will be the y coordinates
	Then do the same for the following rows
	Think of the grid as beign flipped 90 degrees to the right.
	*/

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << A[i + j*m] << " ";
		}
		cout << endl;
	}
	cout << "\n";
}

void Matrix::fillMatrix() {
	for (int i = 0; i < m*n; ++i) {
		A[i] = i;
	}
}

void Matrix::write(string filename) {
	if (m < 1 || n < 1) {
		cout << "Error! No matrix to write to file..." << endl;
		return;
	}
	FILE *fp;
	fp = fopen(filename.c_str(), "wb");
	if (fp == nullptr) {
		cout << "Error! Could not open file..." << endl;
        return;
	}
	fwrite(&m, sizeof(int), 1, fp); // number of rows/x coordinates
	fwrite(&n, sizeof(int), 1, fp); // number of columns/y coordinates
	fwrite(A, sizeof(double), m*n, fp);
	fclose(fp);
}

std::ostream& operator<<(std::ostream& os, const Matrix& M) {
	for (int i = 0; i < M.m; ++i) {
		for (int j = 0; j < M.n; ++j) {
			os << M(i,j) << " ";
		}
		os << "\n";
	}
	return os;
}


