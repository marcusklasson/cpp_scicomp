#include <iostream>
#include <cmath>
#include "asi.hpp"

using namespace std;

// target function is f(x) = 1 + sin(exp(3*x))
double target(double x) {
	return 1 + sin( exp(3*x) );
}

double simpsonRule(FunctionPointer f, double a, double b) {
	return ((b - a) / 6.0) * ( f(a) + 4 * f((a+b)/2) + f(b) );
}

double ASI(FunctionPointer f, double a, double b, double tol) {
	double I1, I2, gamma, errest;
	gamma = 0.5 * (a + b); // mid point
	I1 = simpsonRule(f, a, b);
	I2 = simpsonRule(f, a, gamma) + simpsonRule(f, gamma, b);
	errest = abs(I1 - I2);
	if (errest < 15.0*tol) {
		return I2;
	}
	return ASI(f, a, gamma, tol/2) + ASI(f, gamma, b, tol/2);
}

int main() {
	double I, tol;

	// Write program with for loop over new tolerance!
	tol = 10e-2;
	I = ASI(&target, -1.0, 1.0, tol);
	cout << "I with tol " << tol << " : " << I << endl;

	tol = 10e-3;
	I = ASI(&target, -1.0, 1.0, tol);
	cout << "I with tol " << tol << " : " << I << endl;

	tol = 10e-4;
	I = ASI(&target, -1.0, 1.0, tol);
	cout << "I with tol " << tol << " : " << I << endl;

	return 0; 
}