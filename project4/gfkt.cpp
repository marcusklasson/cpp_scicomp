#include <iostream> 
#include <stdlib.h> 

#include "gfkt.hpp"

using namespace std;

GFkt& GFkt::operator=(const GFkt& U) {
	if (this == &U) {
		return *this;
	}
	u = U.u;
	grid = U.grid;
	return *this;
}

GFkt GFkt::operator+(const GFkt& U) const {
	if (grid != U.grid) { // defined on the same grid?
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		cout << "Exiting..." << endl; 
		exit(EXIT_FAILURE);
	} 
	GFkt tmp(grid);
	tmp.u = u+U.u; // Matrix::operator+()
	return tmp;
}

GFkt GFkt::operator*(const GFkt& U) const {
	if (grid != U.grid) { // defined on the same grid?
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		cout << "Exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	GFkt tmp(grid);
	for (int j = 0; j <= grid->getN(); j++) {
		for (int i = 0; i <= grid->getM(); i++) {
			tmp.u(i,j) = u(i,j) * U.u(i,j);
		}
	}
	return tmp;
}

