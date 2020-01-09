#include <iostream>
#include <vector>

class Point
{
private:
	int m_x = 0;
	int m_y = 0;
	int m_z = 0;
 
public:
	Point(int x, int y, int z)
		: m_x(x), m_y(y), m_z(z)
	{
 
	}
 
	friend std::ostream& operator<<(std::ostream &out, const Point &p)
	{
		out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
		return out;
	}
};

class Shape {

public:
	Shape() {}
	virtual ~Shape() {}

	virtual std::ostream& print(std::ostream& os) const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Shape& S) {
		return S.print(os);
	}
	
};

class Circle : public Shape {
	Point center;
	int radius;

public:
	Circle(const Point& p, int r) : center(p), radius(r) { }
	virtual ~Circle() {}

	virtual std::ostream& print(std::ostream& os) const override {
		os << "Circle(" << center << ", radius " << radius << ")";
		return os;
	}

	const int getRadius() const { return radius;}

};

class Triangle : public Shape {
	Point x, y, z;

public:
	Triangle(const Point& p1, const Point& p2, const Point& p3) 
		: x(p1), y(p2), z(p3) { }
	virtual ~Triangle() {}

	virtual std::ostream& print(std::ostream& os) const override {
		os << "Triangle(" << x << ", " << y << ", " << z << ")";
		return os;
	}
};

const int getLargestRadius(const std::vector<Shape*>& v) {
	int largestRadius = 0;

	for (auto const element : v) {
		if (Circle *c = dynamic_cast<Circle*>(element)) {
			if (c->getRadius() > largestRadius) {
				largestRadius = c->getRadius();
			}
		}
	}
	return largestRadius;
}

int main()
{
    Circle c(Point(1, 2, 3), 7);
    std::cout << c << '\n';
 
    Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
    std::cout << t << '\n';

	std::vector<Shape*> v;
	v.push_back(new Circle(Point(1, 2, 3), 7));
	v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
	v.push_back(new Circle(Point(4, 5, 6), 3));
 
	// print each shape in vector v on its own line here
 
    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function
 
	// delete each element in the vector here
 	for (auto const element : v) {
 		delete element;
 	}
 
    return 0;
}