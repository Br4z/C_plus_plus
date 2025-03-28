#ifndef BOARD_H
#define BOARD_H


class Board {
	private:
		char letter_frequencies[26] = { 0 };
		char** board;
		int columns;
		int rows;

		bool is_valid_coordinate(int x, int y);
	public:
		Board();
		~Board();


		char* get_letters_frecuency();
		int get_columns();
		int get_rows();
		char get_letter(int x, int y);

		void initialize_board(int rows, int columns);
		bool exchange_letters(int x_1, int y_1, int x_2, int y_2);
		void fill_board();

		std::string to_string();
};

#endif
