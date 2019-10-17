#include <iostream>
#include <cmath>
#include <cstdlib>
#include "myexp.hpp"

using namespace std;

double myexp(double x, double tol) {

	int niter = 0;
	double t, sum, pre;
	sum = 1.0; // First element in sum is always equal to 1
	pre = 0.0;
	t = 1.0;
	while (abs(sum-pre) > tol) {
		niter++;
		if (niter > 1000) {
			cout << "No convergence! Returning current sum..." << endl;
			return sum;
			//cerr << "No convergence! Exit calculation..." << endl;
			//exit(1);
		}
		pre = sum;
		cout << "niter = " << niter << endl;
		t = t*(x/niter);
		cout << "t = " << t << endl;
		sum += t;
	} 
	return sum;
}

int main() {

	// Todo: Large negative numbers explode!
	double x = -100;

	cout << "exp(" << x << ") = " << myexp(x) << endl;
	cout << "cmath: " << exp(x) << endl;

	return 0;
}