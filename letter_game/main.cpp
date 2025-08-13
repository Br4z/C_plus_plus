#include <iostream>

#include "Game.h"


int main() {
	int words_length = 3;
	int letters_length = 5;
	std::string* words = new std::string[3]{"apple", "banana", "cherry"};
	// char* letters = Game::fill_letters(letters_length);
	char* letters = new char[5]{'a', 'p', 'p', 'l', 'e'};

	Game game(letters_length, letters, words_length, words);
	std::cout << game.verify_words() << '\n';

	return 0;
}
