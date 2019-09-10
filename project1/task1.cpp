#include <iostream>
#include <cmath>

using namespace std;

double factorial(int n) { // Explicit computation of factorial should be avoided for best results! So there msut be other way
	if (n > 1) {
		return n * factorial(n-1);
	} else {
		return 1;
	}
}

double hornersMethod(int N, double x) {
	// Assuming all coefficients = 1.0
	// Is not stable and doesn't give corret result!
	double result = 1.0;
	//cout << "N: " << N << endl;
	for (int i = 1; i < N; i++) {
		result = result*pow(x,2) + 1.0;
	}
	return result * x; 
}

double sinTaylor(int N, double x) {

	//double result = 0.0;
	double sum = 0.0;
	double firstTerm;
	for (int n = 0; n <= N; n++) {
		
		if (n % 2 == 0) { // This should be possible to make shorter, e.g. with ? 1:-1 or something like that
			firstTerm = 1;
		} else {
			firstTerm = -1;
		}
		//cout << "n = " << n << " firstTerm = " << firstTerm << "\n";
		//sum += firstTerm * pow(x, 2*n+1) / factorial(2*n+1);
		sum += firstTerm * hornersMethod(n, x) / factorial(2*n+1);
	}
	return sum;
}

double cosTaylor(int N, double x) {

	//double result = 0.0;
	unsigned int fact = 1;
	unsigned int sum = 0;
	for (int n = 0; n <= N; ++n) {

		sum += factorial(n);
	}
	return sum;
}

int main() {
	
	int N = 100;
	/* Let user select N later
	cout << "Select number of terms in Taylor series: " << endl;
	cin >> N; */

	double x = 3;

	cout << "Horner's method: " << hornersMethod(N, x) << endl;

	//cout << "Factorial (2N + 1)! = " << sinTaylor(N, x) << " for N = " << N << endl;
	cout << "Taylor series of sin(x) = " << sinTaylor(N, x) << " for N = " << N << endl;
	cout << "sin(1) = " << sin(x) << endl;

	cout << "N+1 term: " << pow(-1.0, N+1) * hornersMethod(N+1, x) / factorial(2*(N+1)+1) << "\n";
	//cout << "Taylor series of sin(x) = " << sinTaylor(N, x) << " for x = " << x << endl;



	return 0;
}