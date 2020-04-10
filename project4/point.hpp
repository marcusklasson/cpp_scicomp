#ifndef POINT_HPP
#define POINT_HPP

class Point {
	double x, y;

public:
	Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { }
	Point(const Point& Q): x(Q.x), y(Q.y) { }
	Point& operator=(const Point& P);
	
	Point& operator=(const double& xx);

	const Point operator-() const;

	const Point& operator+=(const Point& Q);

	const Point operator+(const Point& Q) const;

	~Point() { }
	double getX() const { return x; }
	double getY() const { return y; }
	void zero() { x = y = 0.0; }
};

#endif
