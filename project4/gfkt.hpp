#ifndef GFKT_HPP
#define GFKT_HPP

#include <memory>

#include "domain.hpp"
#include "matrix.hpp"

class GFkt {

private:
	Matrix u;
	//Domain *grid;
	std::shared_ptr<Domain> grid;

public:
	GFkt(std::shared_ptr<Domain> grid_) : u(grid_->getM()+1, grid_->getN()+1), grid(grid_) {}
	GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}
	GFkt& operator=(const GFkt& U);
	GFkt operator+(const GFkt& U) const;
	GFkt operator*(const GFkt& U) const;

};

#endif