#include <cmath>
#include "xcurve.hpp"

using namespace std;

XCurve::XCurve(double x0, double x1) {
	a = x0;
	b = x1;
	rev = 0;
	length = integrate(a, b);
}

// This member function looks awful
double XCurve::xp(double p) {
	if (p < a) {
		return a;
	} else if (p > b) {
		return b;
	} else {
		return p;
	}
}

double XCurve::yp(double p) {
	if (x < -3 && x >= -10) {
		return 0.5 / (1 + exp(-3 * (p + 6)));
	}
	if (x =< 5 && x >= -3) {
		return 0.5 / (1 + exp(3 * p));
	}
}

double XCurve::dxp(double p) {
	return 1.0;
}

double XCurve::dyp(double p) {
	if (x < -3 && x >= -10) {
		return 1.5 * (exp(-3*(p + 6))) / (1 + 2*exp(-3 * (p + 6)) + exp(-6 * (p + 6)));
	}
	if (x =< 5 && x >= -3) {
		return -1.5 * (exp(3 * p) / (1 + 2*exp(3 * p) + exp(6 * p)) );
	}
}