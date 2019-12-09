#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "curvebase.hpp"

class Domain {

private:
	Curvebase *sides[4];
	double *x_, *y_;
	int m_, n_;
	bool checkConsistency();

public:
	Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4);
	//Domain(const Domain&);
	//Domain& operator=(Domain&);
	~Domain();

	void generate_grid(int m, int n);
	
};

#endif