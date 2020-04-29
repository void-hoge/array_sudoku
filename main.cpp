#include <iostream>
#include "board.hpp"
#include "solver.hpp"

int main() {
	std::cout << "sudoku solver" << '\n';
	board bd;
	std::array<std::array<unsigned, SIZE*SIZE>, SIZE*SIZE> hoge = {};
	hoge[0] = {0,6,0,0,2,0,0,3,0};
	hoge[1] = {0,0,1,0,0,5,0,0,4};
	hoge[2] = {7,0,0,8,0,0,2,0,0};
	hoge[3] = {0,0,7,0,0,1,0,0,5};
	hoge[4] = {0,2,0,0,3,0,0,8,0};
	hoge[5] = {9,0,0,4,0,0,7,0,0};
	hoge[6] = {0,0,5,0,0,2,0,0,1};
	hoge[7] = {3,0,0,1,0,0,4,0,0};
	hoge[8] = {0,1,0,0,8,0,0,2,0};

	bd.array_input(hoge);
	bd.show();
	solver slv;
	slv.solve(bd);
	bd.show();
	return 0;
}
