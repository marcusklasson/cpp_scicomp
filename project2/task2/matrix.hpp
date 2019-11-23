#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include <vector>

class Matrix {

private:
	unsigned int mRows;
	unsigned int mCols;
	std::vector<std::vector<double>> matrix;

public:
	Matrix(unsigned int m);
	Matrix(const Matrix &); 

	// From assignment sheet
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	void printMatrix() const;
	void fillMatrix(double x=0.0);	

	// New member functions
	unsigned int getRows() const {return this->mRows;}
	unsigned int getCols() const {return this->mCols;}
	void setMatrixToIdentity();
	double normFrobenius(); 
	Matrix(const std::string&);

};

#endif