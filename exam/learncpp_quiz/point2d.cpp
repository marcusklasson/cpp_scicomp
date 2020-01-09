#include <iostream>
#include <cmath>

class Point2d {
	double x, y;

public:
	Point2d(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { };
	
	//double getX() const {return x;};
	//double getY() const {return y;};
	double distanceTo(const Point2d& P) const;
	friend double distanceTo(const Point2d& P1, const Point2d& P2);
	
	void print();
};

double Point2d::distanceTo(const Point2d& P) const {
	return sqrt((x - P.x)*(x - P.x) + (y - P.y)*(y - P.y));
}

void Point2d::print() {
	std::cout << "Point2d(" << x << ", " << y << ")" << std::endl;
}

double distanceTo(const Point2d& P1, const Point2d& P2) {
	//std::cout << "Inside friend function" << std::endl;
	return sqrt((P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y));
}

 
int main()
{
    Point2d first;
    Point2d second(3.0, 4.0);
    first.print();
    second.print();
    //std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
 	std::cout << "Distance between two points: " << distanceTo(first, second) << '\n';

    return 0;
}