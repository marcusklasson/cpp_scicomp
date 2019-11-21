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
	Matrix(const Matrix &); // Copy constructor. 
	//~Matrix(); // Do I need a destructor?

	// From assignment sheet
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	double norm() const;
	void printMatrix() const;
	void fillMatrix(double x=0.0);	

	// New member functions
	unsigned int getRows() const {return this->mRows;}
	unsigned int getCols() const {return this->mCols;}
	void identity(); // Do I need rthis one?
	Matrix& operator*(double);
	double normFrobenius(); // should it be const here????
	Matrix(const std::string &);

};

#endif