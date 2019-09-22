#include <iostream>
#include <cmath>
#include "taylor.hpp"

using namespace std;
// Got help from:
// https://math.stackexchange.com/questions/184302/create-a-c-program-to-evaluate-the-following-series-sin-x-approx-x-frac

double sinTaylor(int n, double x) {

	// Think about how to make this more general!
	if (x >= 2*M_PI) {
		x = x - 2*M_PI;
	}

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
	// Think about how to make this more general!
	if (x >= 2*M_PI) {
		x = x - 2*M_PI;
	}

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
	
	// User input for N and x?
	//cin >> x;
	int n = 10;
	//cout << "x \t cmath sin(x) \t my sin(x) \t my sin(x) 2" << endl;
	cout << "x \t cmath sin(x) \t my sin(x) \t cmath cos(x) \t my cos(x)" << endl;
	for (int i = -1; i <= 10; ++i) {
		//cout << i << "\t" << sin(i) << "\t " << sinTaylor(n, i) << "\t " << sinTaylorAlternative(n, i) << endl;
		cout << i << "\t" << sin(i) << "\t " << sinTaylor(n, i) << "\t" << cos(i) << "\t " << cosTaylor(n, i) << endl;
	}

	// TODO: fix how we compute the error bound!
	double bound;
	double sinApprox;
	for (int i = -1; i <= 10; ++i) {
		cout << "x \t cmath sin(x) \t my sin(x)" << endl;
		//cout << i << "\t" << sin(i) << "\t " << sinTaylor(n, i) << "\t " << sinTaylorAlternative(n, i) << endl;
		sinApprox = sinTaylor(n, i);
		cout << i << "\t" << sin(i) << "\t " << sinApprox << endl;

		bound =  pow(-1.0, n+1) * sinApprox * (double)(i * i)/ ( (2*(n+1) + 1) * (2*(n+1) ) );
		cout << "Abs error \t n+1'st term" << endl;
		cout << abs(sin(i) - sinApprox) << "\t " << abs(bound) << endl;
	}	


	return 0;
}