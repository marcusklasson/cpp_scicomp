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
	// m are number of x coordinates (columns in matrix)
	// n are number of y coordinates (rows in matrix)
	int m = 50, n = 20;

	// boundary curves of physical domain
	shared_ptr<XCurve> s1 = make_shared<XCurve>(-10.0, 5.0);	// lower horizontal curve
	shared_ptr<YLine> s2 = make_shared<YLine>(0.0, 3.0, 5.0); // right vertical line
	shared_ptr<XLine> s3 = make_shared<XLine>(-10.0, 5.0, 3.0); //upper horizontal line
	shared_ptr<YLine> s4 = make_shared<YLine>(0.0, 3.0, -10.0); // left vertical line 
	
	// generate grid and write to binary file
	cout << "Generate grid" << endl;
	shared_ptr<Domain> grid = make_shared<Domain>(s1, s2, s3, s4);
	grid->generateGrid(m, n);
	//grid->print();
	grid->write("grid.bin");

	// Set grid function u(x, y) = targetFunction()
	GFkt U = GFkt(grid);
	U.setFunction(*targetFunction);
	//U.print();
	
	// Derivative du/dx
	cout << "Derivative of u wrt x" << endl;
	GFkt dux = U.D0x();
	//dux.print();
	dux.write("dux.bin");
	
	// Derivative du/dy
	cout << "Derivative of u wrt y" << endl;
	GFkt duy = U.D0y();
	//duy.print();
	duy.write("duy.bin");

	
	// Laplacian (du/dx)**2 + (du/dy)**2 = du/dt
	cout << "Laplacian" << endl;
	GFkt laplace = U.computeLaplace();
	//laplace.print();
	laplace.write("laplace.bin");
	
	cout << "\nEnd of program.\n" << endl;
	return 0;
}