#ifndef GFKT_HPP
#define GFKT_HPP

#include <memory>
#include <string>

#include "domain.hpp"
#include "matrix.hpp"

typedef double (*FunctionPointer)(Point);

class GFkt {

private:
	Matrix u;
	//Domain *grid;
	std::shared_ptr<Domain> grid;

public:
	GFkt(std::shared_ptr<Domain> grid_) : u( grid_->getXSize()+1, grid_->getYSize()+1), grid(grid_) {}
	GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}
	GFkt& operator=(const GFkt& U); // copy assignment
	GFkt& operator=(GFkt&& U) noexcept; // move assignment
	GFkt operator+(const GFkt& U) const;
	GFkt operator*(const GFkt& U) const;

	void setFunction(const FunctionPointer f); // set grid function values
	GFkt D0x() const;
	GFkt D0y() const;
	GFkt computeLaplace() const;

	void print() const { u.printMatrix(); }
	void writeToFile(std::string fileName) const { u.writeToFile(fileName); } // write to binary file

};

#endif