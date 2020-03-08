#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Matrix {

private:
	int m, n;
	double* A;
	//std::vector<std::vector<double>> matrix;

public:
	Matrix(int m_ = 0, int n_ = 0); 
	Matrix(const Matrix& M); // copy constructor
	//Matrix(Matrix&& M) noexcept; // move constructor
	~Matrix();

	// From assignment sheet
	Matrix& operator=(const Matrix&); // copy assignment
	Matrix& operator=(Matrix&& M) noexcept; // move assignment
	const Matrix& operator+=(const Matrix&);
	const Matrix& operator+=(const double x);

	//const Matrix operator+(const Matrix& M) const;
	Matrix operator+(const Matrix& M) const;
	//friend Matrix operator+(Matrix&& A, const Matrix& B);

	//Matrix& operator*(const Matrix& M) const; // point-wise multiplication
	//Matrix& operator*=(const Matrix&);
	const Matrix& operator*=(const double);
	void printMatrix() const;
	void writeToFile(std::string filename) const; 

	// New member functions
	double& operator()(int row, int col) const;

	int getRows() const {return m;}
	int getCols() const {return n;}
	//void setMatrixToIdentity();
	double normFrobenius(); 
	//Matrix(const std::string&);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& M);

};

#endif