#include <bitset>
#include <iostream>
#include <vector>


std::vector <std::vector <int>> sudoku_input;

bool sudoku_validator(std::vector <std::vector <int>> sudoku) {
	// Check rows
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = j + 1; k < 9; k++)
				if	(sudoku[i][j] == 0)
					break;
				else if (sudoku[i][j] == sudoku[i][k])
					return false;

	// Check columns
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = j + 1; k < 9; k++)
				if	(sudoku[j][i] == 0)
					break;
				else if (sudoku[j][i] == sudoku[k][i])
					return false;

	// Check 3x3 chunks
	for (int i = 0; i < 9; i++) {
		std::bitset <9> bits;
		int initial_row = (int) (i / 3) * 3;
		for (int j = initial_row; j < initial_row + 3; j++) {
			int initial_column = i % 3 * 3;
			for (int k = initial_column; k < initial_column + 3; k++) {
				if (bits[sudoku[j][k] - 1])
					return false;
				else if (sudoku[j][k] != 0)
					bits[sudoku[j][k] - 1] = 1;
			}
		}

		// if (!bits.all())
		// 	return false;
	}

	return true;
}

int main() {
	sudoku_input = {
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

			if (sudoku_input[i][j] == 0)
				std::cout << ". ";
			else
				std::cout << sudoku_input[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << sudoku_validator(sudoku_input);


	return 0;
}
