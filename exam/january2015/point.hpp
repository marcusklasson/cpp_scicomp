
class Point {
	double x, y;

public:
	Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { }
	Point(const Point& Q): x(Q.x), y(Q.y) { }
	Point& operator=(const Point& P) {
		if (this != &P) {
			x = P.x;
			y = P.y;
		}
		return *this;
	}
	
	Point& operator=(const double& xx) {
		x = xx;
		y = 0.0;
		return *this;
	}

	const Point operator-() const {
		return Point(-x,-y);
	}
	const Point& operator+=(const Point& Q) {
		x += Q.x;
		y += Q.y;
		return *this;
	}
	const Point operator+(const Point& Q) const {
		return Point(x+Q.x,y+Q.y);
	}

	friend const Point operator+(const double x, const Point& Q);

	~Point() { }
	double X() const { return x; }
	double Y() const { return y; }
	void zero() { x = y = 0.0; }
};

const Point operator+(const double x, const Point& Q) {
	return Point(x+Q.x,Q.y);
}