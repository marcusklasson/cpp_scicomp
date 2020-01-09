#include <iostream>
#include <cassert> // for assert
#include "matrix.hpp"

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

// Move constructor
Matrix::Matrix(Matrix&& M) : m(M.m), n(M.n), A(M.A) {
	std::cout << "inside move constructor! \n";
	M.m = 0;
	M.n = 0;
	M.A = nullptr;
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
Matrix& Matrix::operator=(Matrix&& M) {

	std::cout << "Inside Move-assignment!\n" << std::endl;
	if (this == &M) {
		return *this;
	}

	delete[] A;
	m = M.m;
	n = M.n;
	A = nullptr;
	if (m*n > 0) {
		for (int i = 0; i < m*n; ++i) {
			A[i] = M.A[i];
		}
	}

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

const double& Matrix::operator()(int row, int col) const {
	// Elements are stored in column-major order
	assert(row >= 0 && row < m);
	assert(col >= 0 && col < n);
	return A[row + col*m]; 
}

Matrix operator+(Matrix&& A, const Matrix& B) {
	assert(A.m == B.m); // Matrix addition requires same size
	assert(A.n == B.n);
	A += B;
	return static_cast<Matrix&&>(A); // use move constructor, same command as std::move(A)
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
