//#include <cmath>
#include <stdio.h> 

#include "domain.hpp"

using namespace std;

GFKT& GFkt::operator=(const GFkt& U) {
	
	if (this == &U) {
		return *this;
	}

	u = U.u;
	grid = U.grid;
	return *this;
}

GFkt GFkt::operator+(const GFkt& U) const {
	if (grid == U.grid) { // defined on the same grid?
		GFkt tmp(grid);
		tmp.u = u+U.u; // Matrix::operator+()
		return tmp;
	} else {
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		return; 
	}
}

GFkt GFkt::operator*(const GFkt& U) const {
	if (grid == U.grid) { // defined on the same grid?
		GFkt tmp(grid);
		for (int j = 0; j <= grid.getN(); j++) {
			for (int i = 0; i <= grid.getM(); i++) {
				tmp.u(i,j) = u(i,j)*U.u(i,j);
			}
		}
		return tmp;
	}
	else {
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		return;
	}
}