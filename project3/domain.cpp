#include <iostream>

#include "domain.hpp"
//#include "curvebase.hpp"

using namespace std;

Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4) {
	sides[0] = &s1;
	sides[1] = &s2;
	sides[2] = &s3;
	sides[3] = &s4;

	//cout << "curve 1 x(s=0): " << sides[0]->x(1) << endl;;
}

Domain::~Domain() {
	if (m_ > 0) {
		delete [] x_;
		delete [] y_;
	}
}

bool Domain::checkConsistency() {
	//double a = (*sides[0]).a;
	//double b = (*sides[0]).b;
	return true;
}