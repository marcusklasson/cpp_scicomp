#include <cmath>
#include "xcurve.hpp"

#include <iostream>

using namespace std;

XCurve::XCurve(double x0, double x1) {
	a = x0;
	b = x1;
	rev = 0;
	length = integrate(a, b);
}

double XCurve::xp(double p) {
	return p;
	/*
	cout << "in xp! p: " << p << endl;
	if (p < a) {
		return a;
	}
	if (p > b) {
		cout << "p är större än b!!!!!!!!!!!!!!!!" << endl;
		return b;
	}
	return p;
	*/
}

double XCurve::yp(double p) {
	if (p < -3) {
		return 0.5 / (1 + exp(-3 * (p + 6)));
	} 
	return 0.5 / (1 + exp(3 * p));
	/*
	else {
		return 0.5 / (1 + exp(3 * p));
	}
	*/
	/*
	if ((p < -3) && (p >= -10)) {
		return 0.5 / (1 + exp(-3 * (p + 6)));
	}
	if ((p <= 5) && (p >= -3)) {
		return 0.5 / (1 + exp(3 * p));
	}
	return p;
	*/
}

double XCurve::dxp(double p) {
	return 1.0;
}

double XCurve::dyp(double p) {
	if (p < -3) {
		return 1.5 * (exp(-3*(p + 6))) / (1 + 2*exp(-3 * (p + 6)) + exp(-6 * (p + 6)));
	}
	return -1.5 * (exp(3 * p) / (1 + 2*exp(3 * p) + exp(6 * p)) );
	/*
	if ((p < -3) && (p >= -10)) {
		return 1.5 * (exp(-3*(p + 6))) / (1 + 2*exp(-3 * (p + 6)) + exp(-6 * (p + 6)));
	}
	if ((p <= 5) && (p >= -3)) {
		return -1.5 * (exp(3 * p) / (1 + 2*exp(3 * p) + exp(6 * p)) );
	}
	return p;
	*/
}