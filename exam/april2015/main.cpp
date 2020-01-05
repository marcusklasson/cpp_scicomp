#include <iostream>
#include "myArray.hpp"
#include "rational.hpp"

using namespace std;

int main() {
	
	myArray<int, 4> intArray;

	for (int i = 0; i < 4; ++i) {
		intArray[i] = i;
	}

	for (int i = 3; i >= 0; --i) {
		cout << intArray[i] << " ";
	}
	cout << "\n";

	myArray<double, 12> doubleArray;

	for (int i = 0; i < 12; ++i) {
		doubleArray[i] = i + 0.5;
	}

	for (int i = 11; i >= 0; --i) {
		cout << doubleArray[i] << " ";
	}
	cout << "\n";

	myArray<Rational, 5> rationalArray;

	rationalArray[0] = Rational(1,2);
	rationalArray[1] = Rational(5,3);
	rationalArray[2] = Rational(10, 8);
	rationalArray[3] = Rational(-1, 1);
	rationalArray[4] = Rational(4, 2);

	for (int i = 4; i >= 0; --i) {
		cout << rationalArray[i] << " ";
	}
	cout << "\n";

	return 0;
}