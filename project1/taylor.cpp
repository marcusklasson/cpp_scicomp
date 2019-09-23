#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include "taylor.hpp"

using namespace std;

// Reduce x to the interval [-pi, pi)
double argumentReduction(double radians) {
	return radians - 2*M_PI*round(radians / (2*M_PI) );
}

double sinTaylor(int n, double x) {

	x = argumentReduction(x);

	int sign = -1;
	double sum, t;
	t = x; // term for n=0 is x
	sum = x; 
	for (int i = 1; i <= n; ++i) {
		t = t * (x * x/((2*i + 1) * (2*i)) );
		sum = sum + sign * t;
		sign = -sign;
	} 
	return sum;
}

double cosTaylor(int n, double x) {

	x = argumentReduction(x);

	int sign = -1;
	double sum, t;
	t = 1.0; // term for n=0 is 1
	sum = 1.0; 	
	for (int i = 1; i <= n; ++i) {
		t = t * (x * x/( (2*i) * (2*i - 1)));
		sum = sum + sign * t;
		sign = -sign;
	}
	return sum;
}

int main() {

	vector<double> x = {-1, 1, 2, 3, 5, 10}; // Values of x for sin(x) and cos(x)
	int n;
	cout << "\nSelect number of terms in Taylor series: ";
	cin >> n;

	double sinx, cosx;
	double sinApprox, cosApprox;
	double error, bound;

	printf("Computing Taylor series of sin(x) and cos(x) using %d terms.\n\n", n);
	cout << "x \t sin(x) \t sinTaylor(x) \t error \t\t bound \t" << endl;
	for (int i = 0; i != x.size(); ++i) {
		sinx = sin(x[i]);
		sinApprox = sinTaylor(n, x[i]);
		error = abs(sinx - sinApprox);
		bound =  pow(-1.0, n+1) * sinApprox * (x[i] * x[i])/ ( (2*(n+1) + 1) * (2*(n+1) ) );
		printf("%.f \t %1.6f \t %1.6f \t %1.6e \t %1.6e \n",
				 x[i], sinx, sinApprox, error, abs(bound));
	}

	cout << "\nx \t cos(x) \t cosTaylor(x) \t error \t\t bound \t" << endl;
	for (int i = 0; i != x.size(); ++i) {
		cosx = cos(x[i]);
		cosApprox = cosTaylor(n, x[i]);
		error = abs(cosx - cosApprox);
		bound =  pow(-1.0, n+1) * cosApprox * (x[i] * x[i])/ ( (2*(n+1)) * (2*(n+1) - 1) );
		printf("%.f \t %1.6f \t %1.6f \t %1.6e \t %1.6e \n",
				 x[i], cosx, cosApprox, error, abs(bound));
	}

	return 0;
}