#include "xline.hpp"

XLine::XLine(double xa, double xb, double y0) {
	a = xa;
	b = xb;
	rev = 0;
	yConst = y0;
	length = xb - xa;
}

double XLine::xp(double p) {
	return p;
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
