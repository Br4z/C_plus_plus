#include <iostream>

#include "Game.h"


Game::Game(int rows, int columns) {
	board.initialize_board(rows, columns);
}

/**
 * Checks if the player has won the game by finding the word on the board.
 *
 * @return true if the player has won, false otherwise.
 */
bool Game::did_player_win() {
	return board.find_word(word, orientation, direction);
}

/**
 * Checks if it is possible to form a word on the game board.
 *
 * @param word The word to check.
 * @return true if it is possible to form the word, false otherwise.
 */
bool Game::is_possible_form_word(std::string_view word) {
	return board.is_possible_form_word(word, orientation);
}

/**
 * Sets the direction of the game.
 *
 * @param direction The direction to set.
 */
void Game::set_direction(DIRECTION direction) {
	this -> direction = direction;
}

/**
 * Sets the orientation of the game.
 *
 * @param orientation The orientation to set.
 */
void Game::set_orientation(ORIENTATION orientation) {
	this -> orientation = orientation;
}

/**
 * Sets the word for the game.
 *
 * This function sets the word for the game and updates the
 * available moves count.
 *
 * @param word The word to be set for the game.
 * @return true if the word is possible and successfully set, false otherwise.
 */
bool Game::set_word(std::string &word) {
	if (is_possible_form_word(word)) {
		this -> word = word;
		available_moves = word.length();
		return true;
	} else
		return false;
}

/**
 * Gets the status of the game.
 *
 * @return true if the game is finished, false otherwise.
 */
bool Game::get_is_game_finished() {
	return game_status;
}

/**
 * Gets the current score of the game.
 *
 * @return a const reference of the score of the game.
 */
const int& Game::get_score() const {
	return score;
}

/**
 * Gets the string representation of the game board.
 *
 * @return the string representation of the game board.
 */
std::string Game::get_string_board() {
	return board.to_string();
}

/**
 * Fills the game board with letters.
 */
void Game::fill_board() {
	board.fill_board();
}

/**
 * Plays a move in the game.
 *
 * This function exchanges letters on the game board at the specified
 * coordinates (x_1, y_1) and (x_2, y_2).
 * If the coordinates are invalid, an error message is printed. Otherwise,
 * the function updates the current move count,
 * checks if the player has won, and updates the score accordingly. If the
 * player has won or reached the maximum number of available moves, the
 * game is finished.
 *
 * @param x_1 The x-coordinate of the first letter to be exchanged.
 * @param y_1 The y-coordinate of the first letter to be exchanged.
 * @param x_2 The x-coordinate of the second letter to be exchanged.
 * @param y_2 The y-coordinate of the second letter to be exchanged.
 */
void Game::play(int x_1, int y_1, int x_2, int y_2) {
	if (!board.exchange_letters(x_1, y_1, x_2, y_2))
		std::cout << "Error: invalid coordinate(s)\n";
	else {
		current_move++;

		bool player_won = did_player_win();
		bool player_reach_available_moves = current_move == available_moves;

		if (player_reach_available_moves) {
			if (player_won) {
				if (2 <= available_moves && available_moves <= 3)
					score += 50;
				else if (4 <= available_moves && available_moves <= 5)
					score += 80;
				else
					score += 100;
			}

			game_status = true;
		} else if (player_won) {
			if (2 <= available_moves && available_moves <= 3)
				score += 50 + (available_moves - current_move) * 20;
			else if (4 <= available_moves && available_moves <= 5)
				score += 80 + (available_moves - current_move) * 40;
			else
				score += 100 + (available_moves - current_move) * 60;
			game_status = true;
		}

		if (player_won)
			std::cout << "Congratulations you won\n";
	}
}

/**
 * Plays the game by taking user input for coordinates and making a move.
 *
 * This function displays the game board, current move, and prompts the
 * user to enter the coordinates for the first and second letter.
 * It then calls the play() function with the adjusted coordinates and continues
 * the game until it is finished.
 */
void Game::play_game() {
	int x_1, y_1, x_2, y_2;

	do {
		std::cout << get_string_board();
		std::cout << "Target word: "<< word << '\n';
		std::cout << "Movement: " << current_move << '\n';

		std::cout << "Enter the coordinates for the first letter (x_1, y_1): ";
		std::cin >> x_1 >> y_1;

		std::cout << "Enter the coordinates for the second letter (x_2, y_2): ";
		std::cin >> x_2 >> y_2;

		play(x_1 - 1, y_1 - 1, x_2 - 1, y_2 - 1);
	} while (!game_status);
}
