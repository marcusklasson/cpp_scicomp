#ifndef YLINE_HPP
#define YLINE_HPP

#include "curvebase.hpp"

class YLine : public Curvebase {

private:
	double xConst;

	double xp(double p);
	double yp(double p);
	double dxp(double p);
	double dyp(double p);

public: 
	YLine(double ya, double yb, double x0);
	
};

#endif