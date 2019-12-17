#include "xline.hpp"

XLine::XLine(double xa, double xb, double y0) {
	a = xa;
	b = xb;
	rev = 0;
	yConst = y0;
	length = xb - xa;
}

double XLine::x(double s) {
	if (s > 1.0) {
		return b;
	}
	return a + s*length;
}

double XLine::y(double s) {
	return yConst;
}

// This member function looks awful
double XLine::xp(double p) {
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

double XLine::yp(double p) {
	return yConst;
}

double XLine::dxp(double p) {
	return 1.0;
}

double XLine::dyp(double p) {
	return 0.0;
}

double XLine::integrate(double a, double b) {
	return (b-a);
} 