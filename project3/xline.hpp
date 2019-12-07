#ifndef XLINE_HPP
#define XLINE_HPP

#include "curvebase.hpp"

class XLine : public Curvebase {

private:
	double yConst;

	double xp(double p);
	double yp(double p);
	double dxp(double p);
	double dyp(double p);
	double integrate(double a, double b);

public: 
	XLine(double xa, double xb, double y0);
	double x(double s);
	double y(double s);
};

#endif