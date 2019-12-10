#include <iostream>

#include "domain.hpp"

using namespace std;

Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4) {
	sides[0] = &s1;
	sides[1] = &s2;
	sides[2] = &s3;
	sides[3] = &s4;

	if (!checkConsistency()) { // Check if corners are connected
		sides[0] = sides[1] = sides[2] = sides[3] = nullptr; // use nullptr instead of NULL to avoid confusion of type.
	}

	m_ = n_ = 0; // Number of grid points
	x_ = y_ = nullptr; // Arrays for grid coordinates
}

Domain::~Domain() {
	if (m_ > 0) {
		delete [] x_;
		delete [] y_;
	}
}

void Domain::generateGrid(int m, int n) {

	if ((m < 1) || (n < 1)) {
		cout << "Error! Both m and n has to be larger than zero." << endl;
		return;
	} else if (!checkConsistency()) {
		cout << "Error! Corners has to be connected when generating grid." << endl;
		return;
	}	

	m_ = m;
	n_ = n;

	// step sizes 
	double h1 = 1.0 / m_; 
	double h2 = 1.0 / n_;

	// Create arrays to carry values for the bound curves in (x,y)-domain
	double *xLow, *xTop, *xLeft, *xRight, *yLow, *yTop, *yLeft, *yRight;
	// Allocate memory. Need to check this if I am actually allocating memory with this command!!!
	xLeft = new double[m_+1];
	yLeft = new double[m_+1];
	xRight = new double[m_+1];
	yRight = new double[m_+1];

	xLow = new double[n_+1];
	yLow = new double[n_+1];
	xTop = new double[n_+1];
	yTop = new double[n_+1];

	// Loop over normalized coordinates and compute its physical coordinates
	for (int i = 0; i <= m_; ++i) {
		xLeft[i] = sides[3]->x(i*h1);
		yLeft[i] = sides[3]->y(i*h1);
		xRight[i] = sides[1]->x(i*h1);
		yRight[i] = sides[1]->y(i*h1);
	}

	for (int j = 0; j <= n_; ++j) {
		xLow[j] = sides[0]->x(j*h2);
		yLow[j] = sides[0]->y(j*h2);
		xTop[j] = sides[2]->x(j*h2);
		yTop[j] = sides[2]->y(j*h2);
	}


	// Allocate memory for arrays with coordinates for entire grid
	x_ = new double[(m_+1)*(n_+1)];
	y_ = new double[(m_+1)*(n_+1)];

	for (int i = 0; i <= m_; ++i) {
		for (int j = 0; j <= n_; ++j) {

			x_[j+i*(n_+1)] = 
				phi0(i*h1)*xLeft[j] 


		}
	}

}

bool Domain::checkConsistency() {
	// check for orientation of lines!
	if ((sides[0]->x(1) != sides[1]->x(0)) && (sides[0]->y(1) != sides[1]->y(0))) {
		cout << "Lower right corner is disconnected!" << endl;
		return false;
	}
	if ((sides[1]->x(1) != sides[2]->x(1)) && (sides[1]->y(1) != sides[2]->y(1))) {
		cout << "Upper right corner is disconnected!" << endl;
		return false;
	}
	if ((sides[2]->x(0) != sides[3]->x(1)) && (sides[2]->y(0) != sides[3]->y(1))) {
		cout << "Upper left corner is disconnected!" << endl;
		return false;
	}
	if ((sides[3]->x(0) != sides[0]->x(0)) && (sides[3]->y(0) != sides[0]->y(0))) {
		cout << "Lower left corner is disconnected!" << endl;
		return false;
	}
	return true;
}