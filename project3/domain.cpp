#include <iostream>
#include <cstdio>
#include <cmath>

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

void Domain::generateGrid(int n, int m) {

	if ((m < 1) || (n < 1)) {
		cout << "Error! Both m and n has to be larger than zero." << endl;
		return;
	} else if (!checkConsistency()) {
		cout << "Error! Corners has to be connected when generating grid." << endl;
		return;
	}	

	n_ = n; // number of grid points in y-direction 
	m_ = m; // number of grid points in x-direction

	// step sizes 
	double h1 = 1.0 / m_; 
	double h2 = 1.0 / n_;

	// Create arrays to carry values for the bound curves in (x,y)-domain
	double *bottomX, *topX, *leftX, *rightX, *bottomY, *topY, *leftY, *rightY;
	// Allocate memory. Need to check this if I am actually allocating memory with this command!!!
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

		cout << bottomY[i] << endl;

		topX[i] = sides[2]->x(i*h1);
		topY[i] = sides[2]->y(i*h1);
	}

	for (int j = 0; j <= n_; ++j) {
		rightX[j] = sides[1]->x(j*h2);
		rightY[j] = sides[1]->y(j*h2);

		leftX[j] = sides[3]->x(j*h2);
		leftY[j] = sides[3]->y(j*h2);
	}

	cout << "print left side points " << endl;
	for (int i = 0; i <= n_; ++i) {
		cout << " (" << leftX[i] << ", " << leftY[i] << ") " << endl;
	}

	cout << "print rightt side points " << endl;
	for (int i = 0; i <= n_; ++i) {
		cout << " (" << rightX[i] << ", " << rightY[i] << ") " << endl;
	}

	cout << "print top side points " << endl;
	for (int i = 0; i <= m_; ++i) {
		cout << " (" << topX[i] << ", " << topY[i] << ") " << endl;
	}

	cout << "print bottom side points " << endl;
	for (int i = 0; i <= m_; ++i) {
		cout << " (" << bottomX[i] << ", " << bottomY[i] << ") " << endl;
	}

	// Allocate memory for arrays with coordinates for entire grid
	x_ = new double[(m_+1)*(n_+1)];
	y_ = new double[(m_+1)*(n_+1)];

	for (int j = 0; j <= n_; ++j ) {
		for (int i = 0; i <= m_; ++i) {
			x_[i+j*(m_+1)] = 
				phi0(i*h1) * leftX[j] 					// left side
				+ phi1(i*h1) * rightX[j]				// right side
				+ phi0(j*h2) * bottomX[i] 					// lower side
				+ phi1(j*h2) * topX[i]					// top side
				- phi0(i*h1) * phi0(j*h2) * bottomX[0]		// lower left corner
				- phi1(i*h1) * phi0(j*h2) * bottomX[m_]	// lower right corner
				- phi0(i*h1) * phi1(j*h2) * topX[0]		// upper left corner
				- phi1(i*h1) * phi1(j*h2) * topX[m_];	// upper right corner

			y_[i+j*(m_+1)] = 
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
	// Print all rows of grid
	cout << "Print grid coordinate values: " << endl;
	for (int i = 0; i < (m_+1)*(n_+1); ++i) {
		cout << " (" << x_[i] << ", " << y_[i] << ") " << endl;
	}
	cout << "Printed all values in grid." << endl;
}

void Domain::write() {
	FILE *fp;
	fp = fopen("outfile.bin", "wb");
	fwrite(&n_, sizeof(int), 1, fp); // why do we need the address here?
	fwrite(&m_, sizeof(int), 1, fp);
	fwrite(x_, sizeof(double), (m_+1)*(n_+1), fp);
	fwrite(y_, sizeof(double), (m_+1)*(n_+1), fp);
	fclose(fp);
}