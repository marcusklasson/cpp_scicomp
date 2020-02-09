#ifndef GFKT_HPP
#define GFKT_HPP

#include "domain.hpp"
#include "matrix.hpp"

class GFkt {

private:
	Matrix u;
	Domain *grid;

public:
	GFkt(Domain *grid_) : u(grid_->getM()+1, grid_->getN()+1), grid(grid_) {}
	GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}
	GFkt& opearator=(const GFkt& U);
	GFkt operator+(const GFkt& U) const;
	GFkt operator*(const GFkt& U) const;

};

#endif