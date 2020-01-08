#include <cmath>
#include "pointModified.hpp"

class Complex : public Point {
	
public:
	Complex(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { };
	Complex(const Complex& C) : x(C.X()), y(C.Y()) { };

	const Complex operator*(const Complex& C) const {
		return Complex( x*C.X() - y*C.Y(), x*C.Y() + y*C.X());
	}

	const Complex operator/(const Complex& C) const {
		return Complex( (x*C.X() + y*C.Y()) / (C.X()*C.X() + C.Y()*C.Y() ), 
						(y*C.X() - x*C.Y()) / (C.X()*C.X() + C.Y()*C.Y() ) );
	}

	const Complex& operator*=(const Complex& C) {
		x = x*C.X() - y*C.Y();
		y = x*C.Y() + y*C.X();
		return *this;
	}

	const Complex& operator/=(const Complex& C) {
		x = (x*C.X() + y*C.Y()) / (C.X()*C.X() + C.Y()*C.Y());
		y = (y*C.X() - x*C.Y()) / (C.X()*C.X() + C.Y()*C.Y() );
		return *this;
	}

	double absolute(const Complex& C) {
		return sqrt( C.X()*C.X() + C.Y()*C.Y() );
	}

};