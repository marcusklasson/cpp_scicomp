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

// Move assignment
GFkt& GFkt::operator=(GFkt&& U) noexcept {
	u = U.u;
	grid = U.grid;
	U.u = Matrix();
	U.grid = nullptr;
	return *this;
}

GFkt GFkt::operator+(const GFkt& U) const {
	if (grid != U.grid) { // defined on the same grid?
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		cout << "Exiting..." << endl; 
		exit(EXIT_FAILURE);
	} 
	GFkt tmp(grid);
	tmp.u = u + U.u; // Matrix::operator+()
	return tmp;
}

GFkt GFkt::operator*(const GFkt& U) const {
	if (grid != U.grid) { // defined on the same grid?
		cout << "Operation has to be defined on the same grid on both lhs and rhs!" << endl;
		cout << "Exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	GFkt tmp(grid);
	for (int j = 0; j <= grid->getYSize(); j++) {
		for (int i = 0; i <= grid->getXSize(); i++) {
			tmp.u(i,j) = u(i,j) * U.u(i,j);
		}
	}
	return tmp;
}

void GFkt::setFunction(const FunctionPointer f) {
	for (int j = 0; j <= grid->getYSize(); ++j ) {
		for (int i = 0; i <= grid->getXSize(); ++i) {
			u(i, j) = f((*grid)(i, j)); 
		}
	}
}

GFkt GFkt::D0x() const {
	GFkt tmp(grid);
	// generate derivative in tmp
	// according to one of the possibilities above
	if (grid->gridValid()) {	
		double dxi, dxj, dyi, dyj, dui, duj;		
		// step sizes 
		double h1 = 1.0 / grid->getXSize(); 
		double h2 = 1.0 / grid->getYSize();
		// loop over all grid points and compute values
		for (int j = 0; j < grid->getYSize(); ++j) {
			for (int i = 0; i < grid->getXSize(); ++i) {

				if (i == 0) {
					dxi = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i+1, j).getX()) + ((*grid)(i+2, j).getX()) ) / (3*h1);
					dyi = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i+1, j).getY()) + ((*grid)(i+2, j).getY()) ) / (3*h1);
					dui = (3 * u(i, j) - 4 * u(i+1, j) + u(i+2, j) ) / (3*h1);
				} else if (i == grid->getXSize()) {
					dxi = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i-1, j).getX()) + ((*grid)(i-2, j).getX()) ) / (3*h1);
					dyi = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i-1, j).getY()) + ((*grid)(i-2, j).getY()) ) / (3*h1);
					dui = (3 * u(i, j) - 4 * u(i-1, j) + u(i-2, j) ) / (3*h1);
				} else {
					dxi = ((*grid)(i+1, j).getX() - (*grid)(i-1, j).getX() ) / (2*h1);
					dyi = ((*grid)(i+1, j).getY() - (*grid)(i-1, j).getY() ) / (2*h1);
					dui = (u(i+1, j) - u(i-1, j) ) / (2*h1);
				}
				
				if (j == 0) {
					dxj = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i, j+1).getX()) + ((*grid)(i, j+2).getX()) ) / (3*h2);
					dyj = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i, j+1).getY()) + ((*grid)(i, j+2).getY()) ) / (3*h2);
					duj = (3 * u(i, j) - 4 * u(i, j+1) + u(i, j+2) ) / (3*h2);
				} else if (j == grid->getYSize()) {
					dxj = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i, j-1).getX()) + ((*grid)(i, j-2).getX()) ) / (3*h2);
					dyj = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i, j-1).getY()) + ((*grid)(i, j-2).getY()) ) / (3*h2);
					duj = (3 * u(i, j) - 4 * u(i, j-1) + u(i, j-2) ) / (3*h2);					 
				} else {
					dxj = ((*grid)(i, j+1).getX() - (*grid)(i, j-1).getX() ) / (2*h2);
					dyj = ((*grid)(i, j+1).getY() - (*grid)(i, j-1).getY() ) / (2*h2);
					duj = (u(i, j+1) - u(i, j-1) ) / (2*h2);					
				}

				tmp.u(i, j) = (dui * dyj - duj * dyi) / (dxi * dyj - dxj * dyi);
			}
		}
	} else {
		cout << "Error! Grid is invalid in D0x" << endl;
		cout << "Exiting..." << endl;
		exit(EXIT_FAILURE);
	}

	return tmp;
}

GFkt GFkt::D0y() const {
	GFkt tmp(grid);
	// generate derivative in tmp
	// according to one of the possibilities above
	if (grid->gridValid()) {	
		double dxi, dxj, dyi, dyj, dui, duj;		
		// step sizes 
		double h1 = 1.0 / grid->getXSize(); 
		double h2 = 1.0 / grid->getYSize();
		// loop over all grid points and compute values
		for (int j = 0; j < grid->getYSize(); ++j) {
			for (int i = 0; i < grid->getXSize(); ++i) {

				if (i == 0) {
					dxi = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i+1, j).getX()) + ((*grid)(i+2, j).getX()) ) / (3*h1);
					dyi = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i+1, j).getY()) + ((*grid)(i+2, j).getY()) ) / (3*h1);
					dui = (3 * u(i, j) - 4 * u(i+1, j) + u(i+2, j) ) / (3*h1);
				} else if (i == grid->getXSize()) {
					dxi = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i-1, j).getX()) + ((*grid)(i-2, j).getX()) ) / (3*h1);
					dyi = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i-1, j).getY()) + ((*grid)(i-2, j).getY()) ) / (3*h1);
					dui = (3 * u(i, j) - 4 * u(i-1, j) + u(i-2, j) ) / (3*h1);
				} else {
					dxi = ((*grid)(i+1, j).getX() - (*grid)(i-1, j).getX() ) / (2*h1);
					dyi = ((*grid)(i+1, j).getY() - (*grid)(i-1, j).getY() ) / (2*h1);
					dui = (u(i+1, j) - u(i-1, j) ) / (2*h1);
				}
				
				if (j == 0) {
					dxj = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i, j+1).getX()) + ((*grid)(i, j+2).getX()) ) / (3*h2);
					dyj = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i, j+1).getY()) + ((*grid)(i, j+2).getY()) ) / (3*h2);
					duj = (3 * u(i, j) - 4 * u(i, j+1) + u(i, j+2) ) / (3*h2);
				} else if (j == grid->getYSize()) {
					dxj = (3 * ((*grid)(i, j).getX()) - 4 * ((*grid)(i, j-1).getX()) + ((*grid)(i, j-2).getX()) ) / (3*h2);
					dyj = (3 * ((*grid)(i, j).getY()) - 4 * ((*grid)(i, j-1).getY()) + ((*grid)(i, j-2).getY()) ) / (3*h2);
					duj = (3 * u(i, j) - 4 * u(i, j-1) + u(i, j-2) ) / (3*h2);					 
				} else {
					dxj = ((*grid)(i, j+1).getX() - (*grid)(i, j-1).getX() ) / (2*h2);
					dyj = ((*grid)(i, j+1).getY() - (*grid)(i, j-1).getY() ) / (2*h2);
					duj = (u(i, j+1) - u(i, j-1) ) / (2*h1);					
				}

				tmp.u(i, j) = (duj * dxi - dui * dxj) / (dxi * dyj - dxj * dyi);
			}
		}
	} else {
		cout << "Error! Grid is invalid in D0y" << endl;
		cout << "Exiting..." << endl;
		exit(EXIT_FAILURE);
	}
	
	return tmp;
}

GFkt GFkt::computeLaplace() const {
	GFkt laplace = D0x()*D0x() + D0y()*D0y(); 
	return laplace;
}