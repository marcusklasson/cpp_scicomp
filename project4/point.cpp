#include "point.hpp"

Point& Point::operator=(const Point& P) {
	if (this != &P) {
		x = P.x;
		y = P.y;
	}
	return *this;
}


Point& Point::operator=(const double& xx) {
	x = xx;
	y = 0.0;
	return *this;
}


const Point Point::operator-() const {
	return Point(-x,-y);
}

const Point& Point::operator+=(const Point& Q) {
	x += Q.x;
	y += Q.y;
	return *this;
}


const Point Point::operator+(const Point& Q) const {
	return Point(x+Q.x, y+Q.y);
}
