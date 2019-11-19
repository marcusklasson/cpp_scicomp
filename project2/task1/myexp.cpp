#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "myexp.hpp"

using namespace std;

double myexp(double x, double tol) {
	/* Calculate exp(x) with Taylor series.
	   If x is negative, then return 1/exp(x) = exp(-x) */
	int niter = 0;
	double t, sum, pre, x1;
	t = 1.0; // First term in sum is always equal to 1
	sum += t; // Add first term to sum 
	pre = 0.0;
	x1 = abs(x); // Use temporary positive x for computing exp(x)
	while (abs(sum-pre) > tol) {
		niter++;
		if (niter > 1000) {
			cout << "No convergence! Returning current sum..." << endl;
			return sum;
		}
		pre = sum;
		t = t*(x1/niter);
		sum += t;
	} 
	if (x < 0) {
		return 1/sum;
	}
	return sum;
}

int main() {

	// Read unknown number of inputs 
	double value;
	vector<double> x;

	cout << "User input values for evaluating exp(x).\n";
	cout << "Use whitespaces between new inputs. End line by pressing Enter + CTRL-d.\n";
	while (cin >> value) {
		x.push_back(value);
	}

	cout << left << setw(15) << "x";
	cout << right << setw(15) << "myexp(x)";
	cout << right << setw(15) << "exp(x)" << endl;
	for (int i = 0; i != x.size(); i++) {
		cout << left << setw(15) << x[i];
		cout << right << setw(15) << myexp(x[i]);
		cout << right << setw(15) << exp(x[i]) << endl;
	}
	return 0;
}