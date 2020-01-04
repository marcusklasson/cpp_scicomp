#include "yline.hpp"

YLine::YLine(double ya, double yb, double x) {
	a = ya;
	b = yb;
	rev = 0;
	xConst = x;
	length = yb - ya;
}

double YLine::x(double s) {
	return xConst;
}

double YLine::y(double s) {
	if (s > 1.0) {
		return b;
	}
	return a + s*length;
}

double YLine::xp(double p) {
	return xConst;
}

// This member function looks awful
double YLine::yp(double p) {
	return p;
	/*
	if (p < a) {
		return a;
	} else if (p > b) {
		return b;
	} else {
		return p;
	}
	*/
}

double YLine::dxp(double p) {
	return 0.0;
}

double YLine::dyp(double p) {
	return 1.0;
}

double YLine::integrate(double a, double b) {
	return (b-a);
} 