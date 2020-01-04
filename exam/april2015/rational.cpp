#include <iostream>
#include <stdlib.h>
#include "rational.hpp"

using namespace std;

Rational::Rational(int pp, int qq) {
	if (qq <= 0) {
		cerr << "Error: q has to be positive!" << endl;
		exit(EXIT_FAILURE);
	}

	p = pp;
	q = qq;
}

Rational::Rational(const Rational& R) {
	p = R.getP();
	q = R.getQ();
}

int Rational::getP() const {
	return p;
}

int Rational::getQ() const {
	return q;
}

Rational& Rational::operator=(const Rational& R) {
	p = R.getP();
	q = R.getQ();
	return *this;
}

const Rational& Rational::operator+=(const Rational& R) {
	p = p*R.getQ() + q*R.getP();
	q = q*R.getQ();
	return *this;
}

const Rational& Rational::operator*=(const Rational& R) {
	p = p*R.getP();
	q = q*R.getQ();
	return *this;
}

const Rational& Rational::operator/=(const Rational& R) {
	p = p*R.getQ();
	q = q*R.getP();
	return *this;
}

const Rational Rational::operator+(const Rational& R) const {
	return Rational( p*R.getQ() + q*R.getP(), q*R.getQ() );
}

const Rational Rational::operator*(const Rational& R) const {
	return Rational( p*R.getP(), q*R.getQ() );
}

const Rational Rational::operator/(const Rational& R) const {
	return Rational( p*R.getQ(), q*R.getP() );
}

ostream& operator<<(ostream& os, const Rational& R) {
	os << "(" << R.getP() << ", " << R.getQ() << ")";
	return os;
}

int main() {
	Rational r(1,2);
	Rational r2(3,4);
	cout << "r: " << r << endl;
	cout << "r2: " << r2 << endl;

	cout << "r + r2: " << (r + r2) << endl;
	cout << "r * r2: " << (r * r2) << endl;
	cout << "r / r2: " << (r / r2) << endl;

	cout << "r += r2: " << (r += r2) << endl;
	r = Rational(1, 2);
	cout << "r *= r2: " << (r *= r2) << endl;
	r = Rational(1, 2);
	cout << "r /= r2: " << (r /= r2) << endl;

	r2 = r;
	cout << "r2 = r -> r2: " << r2 << endl;

	return 0;
}