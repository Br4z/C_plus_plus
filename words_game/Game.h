#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

#include "Board.h"






class Game {
	private:
		Board board;
		bool game_status = false;
		DIRECTION direction;
		int available_moves;
		int current_move = 0;
		int score = 0;
		ORIENTATION orientation;
		std::string word;

		bool did_player_win();
		bool is_possible_form_word(std::string_view word);

	public:
		Game(int rows=10, int columns=10);

		void set_direction(DIRECTION direction);
		void set_orientation(ORIENTATION orientation);
		bool set_word(std::string &word);

		bool get_is_game_finished();
		const int& get_score() const;

		std::string get_string_board();

		void fill_board();
		void play(int x_1, int y_1, int x_2, int y_2);
		void play_game();
};

#endif
