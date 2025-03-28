#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

#include "Board.h"



enum Direction {
	LEFT_TO_RIGHT,
	RIGH_TO_LEFT
};

enum Orientation {
	HORIZONTAL,
	VERTICAL
};


class Game {
	private:
		Board board;
		bool game_status = false;
		Direction direction;
		int available_moves;
		int current_move = 0;
		int score = 0;
		Orientation orientation;
		std::string word;

		bool did_player_win();
		bool is_possible_form_word(std::string word);

	public:
		Game(int rows = 10, int columns = 10);

		void set_direction(Direction direction);
		void set_orientation(Orientation orientation);
		bool set_word(std::string word);

		bool get_is_game_finished();
		int get_score();

		std::string get_string_board();

		void fill_board();
		void play(int x_1, int y_1, int x_2, int y_2);
		void play_game();
};

#endif
