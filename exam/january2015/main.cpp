#include <iostream>
#include "point.hpp"

using namespace std;

int main() {
	
	Point P(1.0, 2.0);
	cout << "(" << P.X() << ", " << P.Y() << ")" << endl;

	return 0;
}