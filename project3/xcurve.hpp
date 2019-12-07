#ifndef XCURVE_HPP
#define XCURVE_HPP

#include "curvebase.hpp"

class XCurve : public Curvebase {

private:
	double xp(double p);
	double yp(double p);
	double dxp(double p);
	double dyp(double p);
	//double integrate(double a, double b);

public: 
	XCurve(double a0, double b0);
	//double x(double s);
	//double y(double s);
};

#endif