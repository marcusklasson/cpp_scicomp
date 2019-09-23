#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include "taylor.hpp"

using namespace std;
// Got help from:
// https://math.stackexchange.com/questions/184302/create-a-c-program-to-evaluate-the-following-series-sin-x-approx-x-frac

double sinTaylor(int n, double x) {

	//cout << "normalized angle: " << x - 2*M_PI*floor((x+M_PI)/(2*M_PI)) << endl;
	// Think about how to make this more general!
	// Must have this otherwise x= 10 gives overflow!
	
	// You must prove this one! Explain how and why you picked it?
	x = x - 2*M_PI*floor((x + M_PI) / (2*M_PI) );

	int sign = -1;
	double sum, t;
	t = x; // term for n=0 is x
	sum = x; 
	for (int i = 1; i <= n; ++i) {
		t = t * (x * x/((2*i + 1) * (2*i)) );
		sum = sum + sign * t;
		//cout << "sum: " << sum << endl;
		sign = -sign;
	} 
    
	return sum;
}

double cosTaylor(int n, double x) {

	x = x - 2*M_PI*floor((x + M_PI) / (2*M_PI) );

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

	vector<int> x = {-1, 1, 2, 3, 5, 10, 15, 100}; // Values of x for sin(x) and cos(x)

	int n;
	cout << "Select number of terms in Taylor series: " << endl;
	//cin >> n;
	n = 10;

	double error, bound;
	double sinApprox, cosApprox;

	cout << "x \t sin(x) \t sinTaylor(x) \t error \t\t bound \t" << endl;
	for (int i = 0; i != x.size(); ++i) {
		sinApprox = sinTaylor(n, x[i]);
		error = abs(sin(x[i]) - sinApprox);
		bound =  pow(-1.0, n+1) * sinApprox * (double)(i * i)/ ( (2*(n+1) + 1) * (2*(n+1) ) );

		printf("%d \t %1.6f \t %1.6f \t %1.6e \t %1.6e \n", x[i], sin(x[i]), sinApprox, error, abs(bound));
		//cout << "normalized angle: " << x[i] - 2*M_PI*floor((x[i]+M_PI)/(2*M_PI)) << endl;
	}

	cout << "\nx \t cos(x) \t cosTaylor(x) \t error \t\t bound \t" << endl;
	for (int i = 0; i != x.size(); ++i) {
		cosApprox = cosTaylor(n, x[i]);
		error = abs(cos(x[i]) - cosApprox);
		bound =  pow(-1.0, n+1) * cosApprox * (double)(i * i)/ ( (2*(n+1)) * (2*(n+1) - 1) );
		printf("%d \t %1.6f \t %1.6f \t %1.6e \t %1.6e \n", x[i], cos(x[i]), cosApprox, error, abs(bound));
	}

	return 0;
}