#include <cstdlib>
#include <string>
#include <time.h>

#include "Board.h"


Board::Board() {

}

Board::~Board() {
	for (int i = 0; i < rows; i++)
		delete board[i];

	delete board;
}


/**
 * Checks if the given coordinates are valid within the board.
 *
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return true if the coordinates are valid, false otherwise.
 */
bool Board::is_valid_coordinate(int x, int y) {
	return (0 <= x && x <= rows) && (0 <= y && y <= columns);
}

/**
 * Creates a copy of the letter frequencies array.
 *
 * @return a copy of the letter frequencies array.
 */
char* Board::get_letters_frecuency() {
	char* copy = new char[26];

	for (int i = 0; i < 26; i++)
		copy[i] = letter_frequencies[i];

	return copy;
}

/**
 * Gets the number of columns in the board.
 *
 * @return the number of columns in the board.
 */
int Board::get_columns() {
	return columns;
}

/**
 * Gets the number of rows in the board.
 *
 * @return the number of rows in the board.
 */
int Board::get_rows() {
	return rows;
}

/**
 * Gets the letter at the specified position on the board.
 *
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @return the letter at the specified position.
 */
char Board::get_letter(int x, int y) {
	return board[y][x];
}

/**
 * Initializes the game board with the specified number of rows and columns.
 *
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 */
void Board::initialize_board(int rows, int columns) {
	this -> rows = rows;
	this -> columns = columns;

	board = new char*[rows];

	for (int i = 0; i < rows; i++)
		board[i] = new char[columns];

	fill_board();
}

/**
 * Exchanges the letters at two given coordinates on the board.
 *
 * This function swaps the letters at the specified coordinates
 * (x_1, y_1) and (x_2, y_2) on the board.
 *
 * @param x_1 The x-coordinate of the first letter.
 * @param y_1 The y-coordinate of the first letter.
 * @param x_2 The x-coordinate of the second letter.
 * @param y_2 The y-coordinate of the second letter.
 * @return true if the exchange was successful, false otherwise.
 */
bool Board::exchange_letters(int x_1, int y_1, int x_2, int y_2) {
	if (is_valid_coordinate(x_1, y_1) &&
		is_valid_coordinate(x_2, y_2)) {
			char temporal = board[y_1][x_1];

			board[y_1][x_1] = board[y_2][x_2];
			board[y_2][x_2] = temporal;

			return true;
		} else
			return false;
}

/**
 * Fills the game board with random letters.
 * Generates a random letter for each cell in the board and updates
 * the letter frequencies.
 */
void Board::fill_board() {
	srand(time(0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			int random_number = rand() % 26;
			char random_letter = 'a' + random_number;

			board[i][j] = random_letter;
			letter_frequencies[random_number] += 1;
		}
}

/**
 * Converts the board to a string representation.
 *
 * @return the string representation of the board.
 */
std::string Board::to_string() {
	std::string result;
	for (int i = 0; i < rows; i++) {
		result += std::to_string(i) + '\t';
		for (int j = 0; j < columns; j++) {
			if (i == 0)
				result += std::to_string(j + 1);
			else
				result += board[i][j];
			result += '\t';
		}
		result += '\n';
	}
	return result;
}
