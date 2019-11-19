#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix {

private:
	unsigned int mRows;
	unsigned int mCols;
	std::vector<std::vector<double>> matrix;

public:
	Matrix(unsigned int m);
	Matrix(unsigned int m, unsigned int n, double val);
	Matrix(const Matrix &); // Copy constructor. 
	//~Matrix(); // Do I need a destructor?

	// from blog post
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	//Matrix transpose();
	Matrix operator+(double);
	Matrix operator-(double);
	//Matrix operator*(double);
	Matrix operator/(double);

	//double& operator[](unsigned&, unsigned&);
	unsigned int getRows() const;
	unsigned int getCols() const; 

	// From assignment sheet
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	double norm() const;
	void printMatrix() const;
	void fillMatrix(double x=0.0);	

	// New member functions
	unsigned int getRows() {return mRows;}
	unsigned int getCols() {return mCols;}
	void identity();
	Matrix& operator*(double);
	double normFrobenius(); // should it be const here????
	Matrix transpose();
	double trace();
	Matrix matrixExponential(double t = 1.0, double tol = 1e-10);

};

#endif