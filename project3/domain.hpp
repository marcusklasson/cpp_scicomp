#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "curvebase.hpp"

class Domain {

private:
	Curvebase *sides[4];
	double *x_, *y_;
	int m_, n_;
	bool checkConsistency();

	// Linear interpolation functions (see slide 13 in Lecture 5 on Structure Grids)
	double phi0(double s) {return 1 - s;}; // phi0(0) = 1, phi0(1) = 0
	double phi1(double s) {return s;}; // phi1(0) = 0, phi1(1) = 1

public:
	Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4);
	//Domain(const Domain&);
	//Domain& operator=(Domain&);
	~Domain();

	// generateGrid() actually generates a grid with n+1 and m+1 points. 
	// Maybe it should be that way, like in linspace() you always need n+1 to get the end point
	void generateGrid(int n, int m); 
	void print();
	void write();
	
};

#endif