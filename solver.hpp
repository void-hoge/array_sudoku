#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "board.hpp"

class solver {
private:
	bool recursion(board& bd);
public:
	void solve(board& bd);
};

#endif
