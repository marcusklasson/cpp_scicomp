#include <iostream>
#include <memory>
#include <cmath>
#include "matrix.hpp"
#include "domain.hpp"
#include "curvebase.hpp"
#include "xcurve.hpp"
#include "xline.hpp"
#include "yline.hpp"
#include "gfkt.hpp"

using namespace std;

double targetFunction(Point p) {
	return sin(p.getX() * p.getX() * 0.01) * cos(p.getX() * 0.1) + p.getY();
}

int main() {
	
	// number of grid points
	int m = 50, n = 20;

	// boundary curves of physical domain
	shared_ptr<XCurve> s1 = make_shared<XCurve>(-10, 5);	// lower horizontal curve
	shared_ptr<YLine> s2 = make_shared<YLine>(0, 3, 5); // right vertical line
	shared_ptr<XLine> s3 = make_shared<XLine>(-10, 5, 3); //upper horizontal line
	shared_ptr<YLine> s4 = make_shared<YLine>(0, 3, -10); // left vertical line 
	
	// generate grid and write to binary file
	cout << "Generate grid" << endl;
	shared_ptr<Domain> grid = make_shared<Domain>(s1, s2, s3, s4);
	grid->generateGrid(m, n);
	grid->print();
	grid->writeToFile("grid.bin");

	// Set grid function u(x, y) = targetFunction()
	GFkt U = GFkt(grid);
	U.setFunction(*targetFunction);

	// Derivative du/dx
	cout << "Compute derivative of u wrt x" << endl;
	GFkt dux = U.D0x();
	dux.print();
	dux.writeToFile("dux.bin");

	// Derivative du/dy
	cout << "Compute derivative of u wrt y" << endl;
	GFkt duy = U.D0y();
	duy.print();
	duy.writeToFile("duy.bin");

	// Laplacian (du/dx)**2 + (du/dy)**2 = du/dt
	cout << "Compute Laplacian" << endl;
	GFkt laplace = U.computeLaplace();
	laplace.print();
	laplace.writeToFile("laplace.bin");

	//cout << "End of program." << endl;
	return 0;
}