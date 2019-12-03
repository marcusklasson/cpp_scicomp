#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
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
	double I;
	vector<double> tol = {10e-2, 10e-3, 10e-4};

	printf("Adaptive Simpson Integration of f(x) = 1 + sin(exp(3*x)): \n");
	printf(" I \t\t tolerance \n");
	for (int i = 0; i != tol.size(); ++i) {
		I = ASI(&target, -1.0, 1.0, tol[i]);
		printf(" %3.6f \t %.e \n", I, tol[i]);
	}

	return 0; 
}