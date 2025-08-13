#include <iostream>
#include <time.h>

#include "Game.h"


Game::Game(int letters_length, char* letters, int words_length, std::string* words)
	: letters_length(letters_length), words_length(words_length), letters(letters), words(words) {
	calculate_letter_frequencies();
}

Game::~Game() {
	delete[] letters;
	delete[] words;
}

/**
 * Generates an array of random lowercase letters.
 *
 * @param letters_length The number of random letters to generate.
 * @return A pointer to a dynamically allocated array containing random lowercase letters.
 *         The caller is responsible for deleting the allocated memory using delete[].
 *
 * @note This function seeds the random number generator with the current time.
 */
char* Game::fill_letters(int letters_length) {
	char* random_letters = new char[letters_length];
	srand(time(NULL));

	for (int i = 0; i < letters_length; i++) {
		int random_number = rand() % 26;
		char random_letter = 'a' + random_number;

		random_letters[i] = random_letter;
	}

	return random_letters;
}

/**
 * Calculates the frequency of each letter in the letters array.
 *
 * This function iterates through the letters array and increments the
 * corresponding index in the letter_frequencies array for each letter found.
 * The letter_frequencies array is indexed from 0 to 25, corresponding to
 * the letters "a" to "z".
 */
void Game::calculate_letter_frequencies() {
	for (int i = 0; i < letters_length; i++) {
		char letter = letters[i];

		letter_frequencies[letter - 'a'] += 1;
	}
}

/**
 * Counts the occurrences of a specific letter in the letters array.
 *
 * This function iterates through the letters array and counts how many times
 * the specified letter appears.
 *
 * @param letter The character to count within the letters array.
 * @return the number of times the specified letter appears in the letters array.
 */
int Game::letter_quantity(char letter) {
	int quantity = 0;
	for(int i = 0; i < letters_length; i++)
		if (letters[i] == letter)
			quantity++;

	return quantity;
}

/**
 * Finds the positions of a given letter in the letters array.
 *
 * This function searches through the letters array and records the positions
 * of the specified letter. It returns an array of integers representing the
 * indices where the letter is found.
 *
 * @param letter The character to search for in the letters array.
 * @return A dynamically allocated array of integers containing the positions
 *         of the specified letter in the letters array. The caller is responsible
 *         for deleting this array to avoid memory leaks.
 */
int* Game::letter_positions(char letter) {
	int length = letter_quantity(letter), index = 0;
	int* positions = new int[length];

	for(int i = 0; i < letters_length; i++)
		if (letters[i] == letter)
			positions[index++] = i;

	return positions;
}

/**
 * Verifies if a given word can be formed using the available letters.
 *
 * This function checks if the provided word can be constructed using the letters
 * available in the game. It temporarily copies the letter frequencies and decrements
 * the count for each letter in the word. If any letter in the word cannot be matched
 * with the available letters, the function returns false.
 *
 * @param word The word to be verified.
 * @return true if the word can be formed using the available letters, false otherwise.
 */
bool Game::verify_word(std::string_view word) {
	int word_length = word.length();
	int temp_frequencies[26];
	std::copy(std::begin(letter_frequencies), std::end(letter_frequencies), std::begin(temp_frequencies));

	for (int i = 0; i < word_length; i++) {
		char letter = word[i];

		if (temp_frequencies[letter - 'a'] == 0)
			return false;
		else
			temp_frequencies[letter - 'a'] -= 1;
	}

	return true;
}

/**
 * Verifies the words in the game and returns a detailed string with the results.
 *
 * This method iterates through each word in the game and checks if the word is valid
 * using the verify_word method. For each valid word, it appends details about each letter
 * in the word to the result string, including the letter itself, its quantity, and its positions
 * in the letters array.
 *
 * @return a detailed string containing the verification results for each valid word.
 */
std::string Game::verify_words() {
	std::string result = "";
	for (int i = 0; i < words_length; i++) {
		std::string word = words[i];

		if (verify_word(word)) {
			result += "Word: " + word + '\n';
			for (char letter : word) {
				result += "\tLetter: " + std::string(1, letter) + " Positions: ";
				int quantity = letter_quantity(letter);
				int* positions = letter_positions(letter);

				result += "[";
				for (int j = 0; j < quantity; j++) {
					result += std::to_string(positions[j]);
					if (j < quantity - 1)
						result += ", ";
				}
				result += "]\n";

				delete[] positions;
			}
			result += '\n';
		}
	}

	return result;
}

std::string Game::to_string() const {
	std::string result = "Letters: [";
	for (int i = 0; i < letters_length; i++) {
		result += letters[i];
		if (i < letters_length - 1)
			result += ", ";
	}

	result += "]\nWords: [";
	for (int i = 0; i < words_length; i++) {
		result += words[i];
		if (i < words_length - 1)
			result += ", ";
	}

	result += "]";

	return result;
}
