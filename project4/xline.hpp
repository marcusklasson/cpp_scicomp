#ifndef XLINE_HPP
#define XLINE_HPP

#include "curvebase.hpp"

class XLine : public Curvebase {

protected:
	double yConst;

	double xp(double p);
	double yp(double p);
	double dxp(double p);
	double dyp(double p);
	
public: 
	XLine(double xa, double xb, double y0);
};

#endif