
#include <iostream>
#include <cmath>

int main() {
	/*
	Find solution for f(x) = x - cos(x) with Newton's algorithm.
	*/
	std::cout << "Give initial guess: " << std::endl;
	double x;
	std::cin >> x;
	double err, tol = 1e-12, x1;
	int it, maxit = 100;
	it = 0;
	err = 1 + tol;
	while (err > tol && it < maxit) {
		x1 = x - (x - cos(x)) / (1 + sin(x));
		err = fabs(x1 - x);
		x = x1;
		++it;
	}
	if (err <= tol) std::cout << "The root is " << x << std::endl;
	else std::cout << "Error, no convergence" << std::endl;
	return 0;
}