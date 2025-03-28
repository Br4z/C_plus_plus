#include <string>

#ifndef GAME_H
#define GAME_H


class Game {
	public:
		int letters_length, words_length;
		char* letters;
		std::string* words;
		int letter_frequencies[26] = { 0 };

		void fill_letters();
		void calculate_letter_frequencies();
		int letter_quantity(char letter);
		int* letter_positions(char letter);
		bool verify_word(std::string word);

	// public:
		Game(int letters_length, std::string* words, int words_length);
		Game(int letters_length, char* letters, std::string* words, int words_length);
		~Game();

		std::string verify_words();

		std::string to_string() const;
};


#endif
