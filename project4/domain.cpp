#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h> 

#include "domain.hpp"

using namespace std;

//Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4) {
Domain::Domain(shared_ptr<Curvebase> s1, shared_ptr<Curvebase> s2, shared_ptr<Curvebase> s3, shared_ptr<Curvebase> s4) {
	sides[0] = s1; //make_shared<Curvebase>(s1); //&s1;
	sides[1] = s2; //make_shared<Curvebase>(s2); // &s2;
	sides[2] = s3; //make_shared<Curvebase>(s3); //&s3;
	sides[3] = s4; //make_shared<Curvebase>(s4); //&s4;

	if (!checkConsistency()) { // Check if corners are connected
		sides[0] = sides[1] = sides[2] = sides[3] = nullptr; 
	}

	m_ = n_ = 0; // Number of grid points, m is number of x coord, n is number of y coord
	x_ = y_ = nullptr; // Arrays for grid coordinates
}

Domain::Domain(const Domain& d) {
	
	m_ = d.m_;
	n_ = d.n_;
	x_ = nullptr;
	y_ = nullptr;
	
	if (m_ > 0) { 
		x_ = new double[(m_+1)*(n_+1)];
		y_ = new double[(m_+1)*(n_+1)];
		for (int i = 0; i < (m_+1)*(n_+1); ++i) {
			x_[i] = d.x_[i];
			y_[i] = d.y_[i];
		}
	}
}

Domain& Domain::operator=(const Domain& d) {
	if (this != &d) { // Don't have to copy itself
		if (m_ == d.m_ && n_ == d.n_) {
			for (int i = 0; i < (m_+1)*(n_+1); ++i) {
				x_[i] = d.x_[i];
				y_[i] = d.y_[i];
			}
		} else {
			if (m_ > 0) { // if grid already exists in this object
				delete [] x_;
				delete [] y_;
				x_ = nullptr;
				y_ = nullptr;
			}
			m_ = d.m_;
			n_ = d.n_;
			if (m_ > 0) { // copy grid points from d to this
				x_ = new double[(m_+1)*(n_+1)];
				y_ = new double[(m_+1)*(n_+1)];
				for (int i = 0; i < (m_+1)*(n_+1); ++i) {
					x_[i] = d.x_[i];
					y_[i] = d.y_[i];
				}
			}
		}
	}
	return *this;
}

Domain::~Domain() {
	if (m_ > 0) {
		delete [] x_;
		delete [] y_;
	}
}

Point Domain::operator()(int i, int j) const {
	if (i < 0 || i > m_ || j < 0 || j > n_) {
		cout << "Error! Both index not within valid range." << endl;
		cout << "Exiting program... \n\n";
		exit(EXIT_FAILURE);
	}
	int idx = j+i*(m_+1);
	return Point(x_[idx], y_[idx]);
}

bool Domain::checkConsistency() {
	// check for orientation of lines!
	if ( abs(sides[0]->x(1) - sides[1]->x(0)) > 1e-3 ||
		 abs(sides[0]->y(1) - sides[1]->y(0)) > 1e-3 ) {
		cout << "Lower right corner is disconnected!" << endl;
		return false;
	}
	if ( abs(sides[1]->x(1) - sides[2]->x(1)) > 1e-3 ||
		 abs(sides[1]->y(1) - sides[2]->y(1)) > 1e-3 ) {
		cout << "Upper right corner is disconnected!" << endl;
		return false;
	}
	if ( abs(sides[2]->x(0) - sides[3]->x(1)) > 1e-3 ||
		 abs(sides[2]->y(0) - sides[3]->y(1)) > 1e-3) {
		cout << "Upper left corner is disconnected!" << endl;
		return false;
	}
	if ( abs(sides[3]->x(0) - sides[0]->x(0)) > 1e-3 ||
		 abs(sides[3]->y(0) - sides[0]->y(0)) > 1e-3 ) {
		cout << "Lower left corner is disconnected!" << endl;
		return false;
	}
	return true;
}

void Domain::generateGrid(int m, int n) {

	if ((m < 1) || (n < 1)) {
		cout << "Error! Both m and n has to be greater than zero." << endl;
		cout << "Exiting program... \n\n";
		exit(EXIT_FAILURE);
	} 

	if (m_ > 0) { // Check if there already exists a grid
		delete [] x_;
		delete [] y_;
	}

	m_ = m; // number of grid points in x-direction
	n_ = n; // number of grid points in y-direction 

	// step sizes 
	double h1 = 1.0 / m_; 
	double h2 = 1.0 / n_;

	// Create arrays to carry values for the bound curves in (x,y)-domain
	// First, create pointers for the arrays
	double *bottomX, *topX, *leftX, *rightX, *bottomY, *topY, *leftY, *rightY;
	// Allocate memory
	bottomX = new double[m_+1];
	bottomY = new double[m_+1];

	topX = new double[m_+1];
	topY = new double[m_+1];

	leftX = new double[n_+1];
	leftY = new double[n_+1];

	rightX = new double[n_+1];
	rightY = new double[n_+1];
	
	for (int i = 0; i <= m_; ++i) {
		bottomX[i] = sides[0]->x(i*h1);
		bottomY[i] = sides[0]->y(i*h1);

		topX[i] = sides[2]->x(i*h1);
		topY[i] = sides[2]->y(i*h1);
	}

	for (int j = 0; j <= n_; ++j) {
		rightX[j] = sides[1]->x(j*h2);
		rightY[j] = sides[1]->y(j*h2);

		leftX[j] = sides[3]->x(j*h2);
		leftY[j] = sides[3]->y(j*h2);
	}

	// Allocate memory for arrays with coordinates for entire grid
	x_ = new double[(m_+1)*(n_+1)];
	y_ = new double[(m_+1)*(n_+1)];
	
	for (int i = 0; i <= m_; ++i ) {
		for (int j = 0; j <= n_; ++j) {
			x_[j+i*(n_+1)] = 
				phi0(i*h1) * leftX[j] 					// left side
				+ phi1(i*h1) * rightX[j]				// right side
				+ phi0(j*h2) * bottomX[i] 					// lower side
				+ phi1(j*h2) * topX[i]					// top side
				- phi0(i*h1) * phi0(j*h2) * bottomX[0]		// lower left corner
				- phi1(i*h1) * phi0(j*h2) * bottomX[m_]	// lower right corner
				- phi0(i*h1) * phi1(j*h2) * topX[0]		// upper left corner
				- phi1(i*h1) * phi1(j*h2) * topX[m_];	// upper right corner

			y_[j+i*(n_+1)] = 
				phi0(i*h1) * leftY[j] 					// left side
				+ phi1(i*h1) * rightY[j]				// right side
				+ phi0(j*h2) * bottomY[i] 					// lower side
				+ phi1(j*h2) * topY[i]					// top side
				- phi0(i*h1) * phi0(j*h2) * bottomY[0]		// lower left corner
				- phi1(i*h1) * phi0(j*h2) * bottomY[m_]	// lower right corner
				- phi0(i*h1) * phi1(j*h2) * topY[0]		// upper left corner
				- phi1(i*h1) * phi1(j*h2) * topY[m_];	// upper right corner

		}
	}

	// Deallocate temporary arrays
	delete [] leftX;
	delete [] rightX;
	delete [] bottomX;
	delete [] topX;
	delete [] leftY;
	delete [] rightY;
	delete [] bottomY;
	delete [] topY;

}

void Domain::print() {
	// Print all rows of grid (for debugging purposes)

	// Printing in cloumn-major order from bottom to up direction
	cout << "Print grid coordinate values: " << endl;
	for (int i = 0; i < (m_+1)*(n_+1); ++i) {
		cout << " (" << x_[i] << ", " << y_[i] << ") " << endl;
	}
	cout << "Printed all values in grid." << endl;
}

void Domain::writeToFile(string filename) {
	FILE *fp;
	fp = fopen(filename.c_str(), "wb");
	fwrite(&n_, sizeof(int), 1, fp); 
	fwrite(&m_, sizeof(int), 1, fp);
	fwrite(x_, sizeof(double), (m_+1)*(n_+1), fp);
	fwrite(y_, sizeof(double), (m_+1)*(n_+1), fp);
	fclose(fp);
}