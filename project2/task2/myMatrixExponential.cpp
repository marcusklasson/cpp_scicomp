#include <iostream>
#include <cmath>
#include "myMatrixExponential.hpp"

using namespace std;

Matrix myMatrixExponential(const Matrix& A, double t, double tol) {
	int niter = 0;
	double t1, pre;
	// Create identity matrix as result for k = 0
	Matrix result(A.getRows());
	result.identity();
	Matrix temp = result;

	//t1 = abs(t); // Don't think you need abs in matrix exponential. Simply compute the power series
	pre = 0.0;
	while (abs(result.normFrobenius() - pre) > tol) {
		++niter;
		if (niter > 1000) {
			cout << "No convergence! Returning current matrix exponential..." << endl;
			return result;
		}
		pre = result.normFrobenius();
		//cout << "previous norm: " << pre << endl;
		temp *= A;  
		temp = temp * (t/niter);
		result += temp;
	}
	return result; 
}