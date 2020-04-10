#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <memory> // for std::shared_ptr
#include "curvebase.hpp"
#include "point.hpp"

class Domain {

private:
	//Curvebase *sides[4];
	std::shared_ptr<Curvebase> sides[4];
	double *x_, *y_;
	int m_, n_;
	bool checkConsistency();

	// Linear interpolation functions (see slide 13 in Lecture 5 on Structure Grids)
	double phi0(double s) { return 1 - s; } // phi0(0) = 1, phi0(1) = 0
	double phi1(double s) { return s; } // phi1(0) = 0, phi1(1) = 1

public:
	//Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4);
	
	Domain(std::shared_ptr<Curvebase> s1,	
		std::shared_ptr<Curvebase> s2, 
		std::shared_ptr<Curvebase> s3, 
		std::shared_ptr<Curvebase> s4);
	
	Domain(const Domain& d);
	Domain& operator=(const Domain& d);
	~Domain();

	Point operator()(int i, int j) const;	// Coordinates at i,j

	int getXSize() const { return m_; }
	int getYSize() const { return n_; }
	bool gridValid() const { return m_ != 0; }

	void generateGrid(int n, int m); 
	void print(); 
	void write(std::string filename);
	
};

#endif