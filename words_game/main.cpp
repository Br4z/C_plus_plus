#include <limits>

#include "Game.h"



void clear_screen() {
	std::cout << std::string(100, '\n');
}


int ask_int_number(std::string_view prompt) {
	int number;

	while (true) {
		std::cout << prompt;
		std::cin >> number;

		if (std::cin.good()) {
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			return number;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cerr << "Error: invalid input. Please write a valid number: " << '\n';
	}
}


int main() {
	std::string string_input;
	int int_input, rows = 4, columns = 4, option = -1;

	std::cout << "/* ------------------------------- WORDS GAME ------------------------------- */" << '\n';

	// std::cout << "Write the number of rows: ";
	// std::getline(std::cin, input);
	// rows = stoi(input);

	// std::cout << "Write the number of columns: ";
	// std::getline(std::cin, input);
	// columns = stoi(input);

	Game game(rows, columns);

	do {
		std::cout << "/* ---------------------------------- MENU ---------------------------------- */" << '\n' <<
					"1. Print the actual board." << '\n' <<
					"2. Fill the board." << '\n' <<
					"3. Play the game with the actual board." << '\n' <<
					"4. Exit." << '\n';
		option = ask_int_number("Write an option: ");
		clear_screen();

		switch (option) {
			case 1:
				std::cout << '\n' << game.get_string_board();
				break;
			case 2:
				game.fill_board();
				break;
			case 3:
			case 4:
				break;
			default:
				std::cout << "Error: invalid option" << '\n';
				break;
		}
	} while (!(option == 3 || option == 4));

	if (option == 3) {
		int_input = ask_int_number("Write the orientation (1. Horizontal, 2. Vertical): ");
		ORIENTATION orientation = (int_input == 1) ? ORIENTATION::HORIZONTAL : ORIENTATION::VERTICAL;

		game.set_orientation(orientation);

		int_input = ask_int_number("Write the direction (1. Normal, 2. Inverted): ");
		DIRECTION direction = (int_input == 1) ? DIRECTION::NORMAL : DIRECTION::INVERTED;

		game.set_direction(direction);

		bool is_valid_word;
		do {
			std::cout << "Write the word: ";
			std::getline(std::cin, string_input);

			is_valid_word = game.set_word(string_input);

			if (!is_valid_word)
				std::cout << "Error: not valid word\n";
		} while(!is_valid_word);

		game.play_game();

		std::cout << "Score: " << game.get_score() << '\n';
	}

	return 0;
}
