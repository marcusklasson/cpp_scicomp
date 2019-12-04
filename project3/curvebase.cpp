#include <iostream>
#include <cmath>
#include "curvebase.hpp"

using namespace std;

// Constrcutor
Curvebase::Curvebase() {} 

double Curvebase::simpsonRule(double a, double b) {
	return ((b - a) / 6.0) * ( dL(a) + 4 * dL((a+b)/2) + dL(b));
}

double Curvebase::dL(double p) {
	return sqrt(dxp(p)*dxp(p) + dyp(p)*dyp(p));
}

double Curvebase::integrate(double a, double b) {
	double I, I1, I2, errest;
	double tol = 1e-8;
	//gamma = 0.5 * (a + b); // mid point
	while (true) {
		I1 = simpsonRule(f, a, b);
		I2 = simpsonRule(f, a, 0.5*(a+b)) + simpsonRule(f, 0.5*(a+b), b);
		errest = abs(I1 - I2);
		if (errest < 15.0*tol) {
			return I2;
		}

	}


	return integrate(f, a, gamma, tol/2) + integrate(f, gamma, b, tol/2);

	return I;
}

double Curvebase::newtonMethod(double p0, double s) {
	double err = 1.0, tol = 1e-12;
	int it = 0, maxit = 100;
	double p, p1;
	p = p0;

	while (err > tol && it < maxit) {
		p1 = p - integrate(a, p) / dL(p);
		err = fabs(p1 - p);
		p = p1;
		++it;
	}
	if (it == maxIt) {
		cout << "Error, no convergence in Newton's method!" << endl;
	}
	return p;
}