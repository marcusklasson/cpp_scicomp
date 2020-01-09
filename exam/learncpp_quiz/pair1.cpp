#include <iostream>

template <class T>
class Pair1 {
private:
	T x;
	T y;

public:
	Pair1(const T& xx, const T& yy){
		x = xx;
		y = yy;
	}

	const T& first() const {return x;};
	const T& second() const {return y;};
};

int main()
{
	Pair1<int> p1(5, 8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 
	const Pair1<double> p2(2.3, 4.5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
 
	return 0;
}