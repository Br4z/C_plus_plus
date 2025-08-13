#include <bitset>
#include <iostream>
#include <vector>


constexpr int GRID_SIZE = 9;


bool is_sudoku_valid(const std::vector <std::vector <int>> &board) {
	std::vector <std::bitset <GRID_SIZE>> row_checker(GRID_SIZE);
	std::vector <std::bitset <GRID_SIZE>> col_checker(GRID_SIZE);
	std::vector <std::bitset <GRID_SIZE>> box_checker(GRID_SIZE);

	for (int r = 0; r < GRID_SIZE; r++)
		for (int c = 0; c < GRID_SIZE; c++) {
			if (board[r][c] == 0)
				continue;

			int num = board[r][c] - 1; // Bitset is 0-indexed, numbers are 1-9

			// Check if the number has already been in the current row
			if (row_checker[r][num])
				return false;

			row_checker[r][num] = 1;

			// Check if the number has already been in the current column
			if (col_checker[c][num])
				return false;

			col_checker[c][num] = 1;

			int box_index = (r / 3) * 3 + (c / 3);
			// Check if the number has already been in the current 3x3 box
			if (box_checker[box_index][num])
				return false;

			box_checker[box_index][num] = 1;
		}

	return true;
}


int main() {
	std::vector <std::vector <int>> board = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	// Print the sudoku puzzle to verify
	std::cout << "Sudoku Puzzle:\n";
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i != 0)
			std::cout << "---------------------\n";
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0)
				std::cout << "| ";

			if (board[i][j] == 0)
				std::cout << ". ";
			else
				std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout << "Is the puzzle valid? " << std::boolalpha << is_sudoku_valid(board) << '\n';

	return 0;
}
