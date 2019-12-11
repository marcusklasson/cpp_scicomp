#include <iostream>
#include <cmath>
#include "curvebase.hpp"

using namespace std;

// Constructor
Curvebase::Curvebase() {} 

double Curvebase::simpsonRule(double a, double b) {
	return ((b - a) / 6.0) * ( dL(a) + 4.0 * dL(0.5*(a+b)) + dL(b));
}

double Curvebase::dL(double p) {
	return sqrt(dxp(p)*dxp(p) + dyp(p)*dyp(p));
}

double Curvebase::integrate(double a, double b) {
	/* Compute adaptive simpson integration using tree. 
	 * Assume that the full tree already exist and 
	 * depending on if the error is lower than the tolerance
	 * we move down to one level of nodes in the tree and 
	 * compute the integral for that part of the interval.
	 * Then we have to traverse through all nodes on that
	 * level and sum all the computed integrals on these 
	 * partitions of the interval.
	 */
	//cout << "In integration... "<< endl;
	double I = 0.0, I1, I2, errest;
	double tol = 1e-6;
	int node = 1;
	while (true) {
		I1 = simpsonRule(a, b);
		I2 = simpsonRule(a, 0.5*(a+b)) + simpsonRule(0.5*(a+b), b);
		errest = abs(I1 - I2);
		//cout << "Node: " << node << endl;
		if (errest < 15.0*tol) { // acceptable errest and in leaf
			I += I2;
			//cout << "Node: " << node << endl;
			/* while odd node, traverse up
			 * until first even node
			 */
			while (node % 2 != 0) {
				if (node == 1) { // if root node
					return I;
				}
				node = 0.5 * node;
				a = (2 * a) - b;
				tol *= 2; 
			}
			/* if even node, move up to parent node
			 * and then go to right child node
			 */
			node = 0.5*node;
			b = (2 * b) - a;
			node = 2*node + 1;
			a = 0.5 * (a+b);
		} 
		// go to left child node
		else { 
			node *= 2; // increase number of nodes
			b = 0.5 * (a+b); // decrease upper limit on interval 
			tol *= 0.5; // decrease tolerance
		}

	}
}

double Curvebase::newtonMethod(double p0, double s) {
	double err = 1.0, tol = 1e-6;
	int it = 0, maxit = 100;
	double p, p1;
	p = p0;

	while (err > tol && it < maxit) {
		p1 = p - (integrate(a, p) - s*length) / dL(p);
		err = fabs(p1 - p);
		p = p1;
		++it;
	}
	if (it == maxit) {
		cout << "Error, no convergence in Newton's method!" << endl;
	}
	return p;
}

double Curvebase::x(double s) {
	// Could check that s is in [0, 1]
	double p, p0;
	p0 = a + s * length; // initial guess for newton's method
	p = newtonMethod(p0, s);
	//cout << "From newtons method p = " << p << endl;
	return xp(p);
}

double Curvebase::y(double s) {
	// Could check that s is in [0, 1]
	double p, p0;
	p0 = a + s * length; // initial guess for newton's method
	p = newtonMethod(p0, s);
	return yp(p);
}