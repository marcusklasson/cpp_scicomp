#include <iostream>

class Average {
	std::int_least32_t sum;
	std::int_least8_t N;

public:
	Average() : sum(0), N(0){ };

	Average& operator+=(const int x);
	friend std::ostream& operator<<(std::ostream& os, const Average& avg);
};

Average& Average::operator+=(const int x) {
	++N;
	sum += x;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Average& A) {
	if (A.N == 0) {
		os << A.sum;
		return os;
	}
	os << static_cast<double>(A.sum) / A.N;
	return os;
}

int main()
{
	Average avg{};
	
	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4
	
	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6
 
	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12
 
	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5
 
	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7
 
	Average copy{ avg };
	std::cout << copy << '\n';
 
	return 0;
}