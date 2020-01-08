#include "yline.hpp"

YLine::YLine(double ya, double yb, double x) {
	a = ya;
	b = yb;
	rev = 0;
	xConst = x;
	length = yb - ya;
}

double YLine::xp(double p) {
	return xConst;
}

double YLine::yp(double p) {
	return p;
}

double YLine::dxp(double p) {
	return 0.0;
}

double YLine::dyp(double p) {
	return 1.0;
}

