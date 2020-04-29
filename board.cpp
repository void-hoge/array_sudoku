#include "board.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

board::board() {
	for (auto &i: cells) {
		for (auto &j: i) {
			j = 0;
		}
	}
	turn = 0;
}

bool board::set(const int x, const int y, const int num) {
	if (cells[x][y] != 0) {
		return false;
	}
	history.push_back(x*SIZE*SIZE+y);
	cells[x][y] = num;
	turn++;
	return true;
}

bool board::undo() {
	if (turn <= 0) {
		return false;
	}
	cells[*(history.end()-1)/(SIZE*SIZE)][*(history.end()-1)%(SIZE*SIZE)] = 0;
	history.pop_back();
	turn--;
	return true;
}

std::vector<unsigned> board::get_movable(const int x, const int y) const{
	std::vector<unsigned> result;
	if (cells[x][y] != 0) {
		return result;
	}
	for (unsigned i = 0; i <= SIZE*SIZE; i++) {
		result.push_back(i);
	}
	for (int i = 0; i < cells.size(); i++) {
		result[cells[x][i]] = 0;
		result[cells[i][y]] = 0;
	}
	int block_x = x/SIZE;
	int block_y = y/SIZE;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			result[cells[block_x*SIZE+i][block_y*SIZE+j]] = 0;
		}
	}
	std::sort(result.begin(), result.end());
	result.erase(std::unique(result.begin(), result.end()), result.end());
	result.erase(result.begin());
	return result;
}

unsigned board::get_first_blank() const {
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			if (cells[i][j] == 0) {
				return i*SIZE*SIZE+j;
			}
		}
	}
	return ~0;
}

bool board::isfinish() const {
	static auto factorial = [](unsigned n){
		unsigned result = 1;
		for (unsigned i = 2; i <= n; i++) {
			result *= i;
		}
		return result;
	};
	static const unsigned check_num = factorial(SIZE*SIZE);
	std::array<unsigned, SIZE*SIZE> vertical_check;
	std::array<unsigned, SIZE*SIZE> horizontal_check;
	for (int i = 0; i < vertical_check.size(); i++) {
		vertical_check[i] = 1;
		horizontal_check[i] = 1;
	}
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			horizontal_check[i] *= cells[i][j];
			vertical_check[i] *= cells[j][i];
		}
	}
	for (int i = 0; i < horizontal_check.size(); i++) {
		if (horizontal_check[i] != check_num) {
			return false;
		}
		if (vertical_check[i] != check_num) {
			return false;
		}
	}

	std::array<unsigned, SIZE*SIZE> block_check;
	for (auto &i: block_check) {
		i = 1;
	}
	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++) {
			block_check[(i/SIZE)*SIZE+(j/SIZE)] *= cells[i][j];
		}
	}
	for (int i = 0; i < block_check.size(); i++) {
		if (block_check[i] != check_num) {
			return false;
		}
	}
	return true;
}

void board::array_input(const std::array<std::array<unsigned, SIZE*SIZE>, SIZE*SIZE>& in) {
	cells = in;
}

void board::show() const{
	for (int i = 0; i < cells.size(); i++) {
		if ((i % SIZE) == 0) {
			for (int j = 0; j < SIZE*SIZE*3+SIZE+1; j++) {
				if ((j % (SIZE*3+1)) == 0) {
					std::cout << '+';
				}else {
					std::cout << '-';
				}
			}
			std::cout << '\n';
		}
		for (int j = 0; j < cells[i].size(); j++) {
			if ((j % SIZE) == 0) {
				std::cout << '|';
			}
			std::cout << std::setw(3) << cells[i][j];
		}
		std::cout << '|' << '\n';
	}
	for (int i = 0; i < SIZE*SIZE*3+SIZE+1; i++) {
		if ((i % (SIZE*3+1)) == 0) {
			std::cout << '+';
		}else {
			std::cout << "-";
		}
	}
	std::cout << '\n';
}
