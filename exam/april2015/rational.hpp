#ifndef RATIONAL_HPP
#define RATIONAL_HPP

using namespace std;

class Rational {

public:
	Rational() {};
	Rational(int pp, int qq);
	Rational(const Rational& R);
	~Rational() {};

	int getP() const;
	int getQ() const;

	Rational& operator=(const Rational& R);
	const Rational& operator+=(const Rational& R);
	const Rational& operator*=(const Rational& R);
	const Rational& operator/=(const Rational& R);

	const Rational operator+(const Rational& R) const;
	const Rational operator*(const Rational& R) const;
	const Rational operator/(const Rational& R) const;

	const Rational operator*(const int& pp) const;

	friend const Rational operator*(const int pp, const Rational& R);

	friend ostream& operator<<(ostream& os, const Rational& R);

private:
	int p; 
	int q;
};

#endif