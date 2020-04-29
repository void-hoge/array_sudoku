#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <array>

const unsigned SIZE = 3;

class board {
private:
	std::array<std::array<unsigned, SIZE*SIZE>, SIZE*SIZE> cells;
	std::vector<unsigned> history;
	int turn;
public:
	board();
	bool set(const int x, const int y, const int num);
	bool undo();
	unsigned get_first_blank() const;
	std::vector<unsigned> get_movable(const int x, const int y) const;
	bool isfinish() const;
	void array_input(const std::array<std::array<unsigned, SIZE*SIZE>, SIZE*SIZE>&);
	void show() const;
};

#endif
