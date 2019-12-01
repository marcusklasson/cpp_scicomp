#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

class Curvebase {

protected:
	double pmin; // minimal value for p
	double pmax; // maximal value for p
	bool rev; // orientation of the curve
	double length;

	virtual double xp(double p) = 0;
	virtual double yp(double p) = 0;
	virtual double dxp(double p) = 0;
	virtual double dyp(double p) = 0;
	double integrate(double p); //arc length integral

public:
	Curvebase(); //constructor
	double x(double s); //arc length parametrization
	double y(double s); //arc length parametrization

};

#endif