#include <iostream>
#include <cmath>
#include "myMatrixExponential.hpp"

using namespace std;

Matrix myMatrixExponential(const Matrix& A, double tol) {
	int niter = 0;
	double pre = 0.0;
	// Create identity matrix as result for k = 0
	Matrix result(A.getRows());
	result.setMatrixToIdentity();
	Matrix temp = result;

	while (abs(result.normFrobenius() - pre) > tol) {
		++niter;
		if (niter > 1000) {
			cout << "No convergence! Returning current matrix exponential..." << endl;
			return result;
		}
		pre = result.normFrobenius();
		temp *= A;  
		temp *= (1.0/niter);
		result += temp;
	}
	cout << "Number of iterations K = " << niter << endl;
	return result; 
}