#include <iostream>

#include "Game.h"

void clear_screen() {
	std::cout << std::string(100, '\n');
}

template <typename T>
T prompt_for_numeric(const std::string &message) {
	while (true) {
		std::cout << message;
		std::string line;
		std::getline(std::cin, line);
		try {
			if constexpr (std::is_same_v <T, int>)
				return std::stoi(line);
			else if constexpr (std::is_same_v <T, float>)
				return std::stof(line);
		} catch (const std::exception &) {
			std::cerr << "Invalid input. Please enter a valid number.\n";
		}
	}
}

std::string prompt_for_string(const std::string &message) {
	std::cout << message;
	std::string line;
	std::getline(std::cin, line);
	return line;
}

/* -------------------------------------------------------------------------- */

void add_predator_to_entity(Game &game) {
	std::cout << game.list_entities() << '\n';
	int prey_id = prompt_for_numeric <int>("Enter the entity ID to which you want to assign a predator: ");
	int predator_id = prompt_for_numeric <int>("Enter the predator ID: ");
	try {
		game.add_predator_to_entity(prey_id, predator_id);
		std::cout << "Predator relationship added successfully.\n";
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void consult_entity(Game &game) {
	std::cout << game.list_entities() << '\n';
	int entity_id = prompt_for_numeric <int>("Enter the entity ID to consult: ");
	try {
		std::cout << game.consult_entity(entity_id) << '\n';
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void play(Game &game, bool debug_mode) {
	std::string game_status;

	do {
		clear_screen();
		std::cout << (debug_mode ? game.debug() : game.to_string()) << '\n';
		std::cout << game.list_entities() << '\n';

		int action = prompt_for_numeric <int>("Enter action:\n1. Move the boat.\n2. Move an entity.\n-> ");

		try {
			if (action == 1)
				game.move_boat();
			else if (action == 2) {
				int entity_id = prompt_for_numeric <int>("Enter entity ID to move: ");
				int direction_val = prompt_for_numeric <int>("Enter direction (1 for Left, 2 for Right): ");

				if (direction_val != 1 && direction_val != 2) {
					std::cout << "Invalid direction. Try again.\n";
					continue;
				}

				DIRECTION direction = (direction_val == 1) ? DIRECTION::LEFT : DIRECTION::RIGHT;
				game.move_entity(entity_id, direction);
			} else {
				std::cerr << "Error: invalid action. Try again \n";
			}
			game_status = game.game_status();
		} catch (const std::exception &e) {
			std::cerr << "Error during move: " << e.what() << '\n';
			prompt_for_string("Press Enter to acknowledge.");
		}
	} while (game_status.empty());

	clear_screen();
	std::cout << "--- Game Over ---\n" << game_status << '\n';
}


int main(int argc, char* argv[]) {
	bool debug_mode = (argc > 1 && std::string(argv[1]) == "debug");

	int additional_entities = prompt_for_numeric <int>("Enter the number of additional entities the game will have: ");
	Game game(additional_entities, 2);

	for (int i = 0; i < additional_entities; i++) {
		std::string name = prompt_for_string("Enter name for entity #" + std::to_string(i + 1) + ": ");
		game.add_entity(name);
	}

	clear_screen();

	const std::string menu =
		"========================\n"
		" Welcome to the Boat Game\n"
		"========================\n"
		"1. List entities\n"
		"2. Add predator to entity\n"
		"3. Consult entity information\n"
		"4. Play Game\n"
		"5. Exit\n"
		"-> ";

	bool running = true;
	while (running) {
		int option = prompt_for_numeric <int>(menu);
		clear_screen();

		if (option == 5) {
			std::cout << "Exiting game. Goodbye!\n";
			break;
		}

		switch (option) {
			case 1:
				std::cout << "--- Current Entities ---\n" << game.list_entities() << '\n';
				break;
			case 2:
				add_predator_to_entity(game);
				break;
			case 3:
				consult_entity(game);
				break;
			case 4:
				play(game, debug_mode);
				running = false;
				break;
			default:
				std::cout << "Invalid option. Please try again.\n";
				break;
		}
		prompt_for_string("\nPress Enter to return to the menu...");
		clear_screen();
	}

	return 0;
}
