#include <string>

#ifndef GAME_H
#define GAME_H


class Game {
	private:
		int letters_length, words_length;
		char* letters;
		std::string* words;
		int letter_frequencies[26] = { 0 };

		void calculate_letter_frequencies();
		int letter_quantity(char letter);
		int* letter_positions(char letter);
		bool verify_word(std::string_view word);

	public:
		Game(int letters_length, char* letters, int words_length, std::string* words);
		~Game();

		static char* fill_letters(int letters_length);

		std::string verify_words();

		std::string to_string() const;
};


#endif
