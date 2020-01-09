#include <iostream>

template <class T1, class T2>
class Pair {

private:
	T1 m_x;
	T2 m_y;

public:
	Pair(const T1& x, const T2& y) {
		m_x = x;
		m_y = y;
	}

	const T1& first() const {return m_x;}
	const T2& second() const {return m_y;}
};

int main()
{
	Pair<int, double> p1(5, 6.7);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 
	const Pair<double, int> p2(2.3, 4);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
 
	return 0;
}