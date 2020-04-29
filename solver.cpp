#include "solver.hpp"
#include "board.hpp"
#include <iostream>

void solver::solve(board& bd) {
	if (bd.isfinish() == true) {
		return;
	}
	const unsigned idx = bd.get_first_blank();
	if (idx == ~0) {
		return;
	}
	const unsigned idx_x = idx/(SIZE*SIZE);
	const unsigned idx_y = idx%(SIZE*SIZE);
	std::vector<unsigned> movable = bd.get_movable(idx_x, idx_y);
	for (int i = 0; i < movable.size(); i++) {
		bd.set(idx_x, idx_y, movable[i]);
		if (recursion(bd) == true) {
			return;
		}
		bd.undo();
	}
}

bool solver::recursion(board& bd) {
	if (bd.isfinish() == true) {
		return true;
	}
	const unsigned idx = bd.get_first_blank();
	if (idx == ~0) {
		return false;
	}
	const unsigned idx_x = idx/(SIZE*SIZE);
	const unsigned idx_y = idx%(SIZE*SIZE);
	std::vector<unsigned> movable = bd.get_movable(idx_x, idx_y);
	for (int i = 0; i < movable.size(); i++) {
		bd.set(idx_x, idx_y, movable[i]);
		if (recursion(bd) == true) {
			return true;
		}
		bd.undo();
	}
	return false;
}
