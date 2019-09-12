#include <iostream>
#include <cmath>

using namespace std;

unsigned long factorial(int n) { // Explicit computation of factorial should be avoided for best results! So there must be other way
	if (n > 1) {
		return n * factorial(n-1);
	} else {
		return 1;
	}
}

double hornersMethod(int N, double x) {
	// Assuming all coefficients = 1.0
	// Is not stable and doesn't give corret result!
	//double result = 1.0;
	double result = 1.0 / factorial(0);
	//cout << "N: " << N << endl;
	for (int i = 1; i <= N; i++) {
		//result = result*x*x + 1.0;
		result = result*x*x + pow(-1.0, i)/factorial(2*i);
	}
	return result; 
}

double sinTaylor(int N, double x) {
	
	double result = pow(-1.0, N) / factorial(2*N + 1);
	for (int n = N-1; n >= 0; n--) {
		result = result*x*x + pow(-1.0, n) / factorial(2*n + 1);
		
	}
	return result*x;
}

double cosTaylor(int N, double x) {

	double result = pow(-1.0, N) / factorial(2*N);

	for (int n = N-1; n > 0; n--) {
		result = result*x*x + pow(-1.0, n) / factorial(2*n);
	}
	result = result*x*x + 1.0; // n = 0
	return result;
	
}


// Alternative solution. Didn't work much better
double cosTaylorAlternative(int N, double x) {

	//double result = pow(-1.0, N) / factorial(2*N);

	// Compute factorial of N
	unsigned long fact = 1;
	for (int i = 1; i <= 2*N; i++) {
		fact = fact * i;
	}
	//cout << "factorial: " << fact << endl;
	double result = pow(-1.0, N) / fact;

	//for (int n = N-1; n >= 0; n--) {
	for (int n = N-1; n > 0; n--) {
		//result = result*x*x + pow(-1.0, n) / factorial(2*n);
		//cout << "n: " << n << endl;
		fact =  fact / ((2*(n + 1)) * (2*(n + 1)-1));
		
		//cout << "factorial: " << fact << endl;
		result = result*x*x + pow(-1.0, n) / fact;
		
	}
	result = result*x*x + 1.0; // n = 0
	return result;
	
}


/*
Works for small x and N <= 15.
I guess it's the factorial that messes it up,
so I need to find another way.
Also need to write in C++ style with header file and so on.
*/
int main() {
	
	// User input for N and x?
	int N = 3;
	double x = 5;

	cout << "Taylor series of sin(x) = " << sinTaylor(N, x) << " for N = " << N << endl;
	cout << "True sin(x) = " << sin(x) << endl;

	cout << "Taylor series of cos(x) = " << cosTaylor(N, x) << " for N = " << N << endl;
	cout << "True cos(x) = " << cos(x) << endl;

	cout << "Taylor series of cos(x) = " << cosTaylorAlternative(N, x) << " for N = " << N << endl;
	cout << "True cos(x) = " << cos(x) << endl;

	return 0;
}