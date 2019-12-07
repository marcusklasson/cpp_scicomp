#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

class Curvebase {

protected:
	double a; //pmin; // minimal value for p
	double b; //pmax; // maximal value for p
	bool rev; // orientation of the curve
	double length;

	virtual double xp(double p) = 0;
	virtual double yp(double p) = 0;
	virtual double dxp(double p) = 0;
	virtual double dyp(double p) = 0;

	virtual double integrate(double a, double b); //arc length integral
	double newtonMethod(double p0, double s); // Newton solver
	double simpsonRule(double a, double b);
	double dL(double p); // integrand of arc length


public:
	Curvebase(); //constructor
	virtual double x(double s); //arc length parametrization
	virtual double y(double s); //arc length parametrization

};

#endif