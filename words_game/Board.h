#ifndef BOARD_H
#define BOARD_H


enum class DIRECTION {
	NORMAL,
	INVERTED
};

enum class ORIENTATION {
	HORIZONTAL,
	VERTICAL
};

class Board {
	private:
		char letter_frequencies[26];
		char** board;
		int columns;
		int rows;

		bool is_valid_coordinate(int x, int y);
	public:
		Board();
		~Board();

		const int& get_columns() const;
		const int& get_rows() const;
		bool is_possible_form_word(std::string_view word, ORIENTATION orientation) const;
		bool find_word(std::string_view word, ORIENTATION orientation, DIRECTION direction) const;

		void initialize_board(int rows, int columns);
		bool exchange_letters(int x_1, int y_1, int x_2, int y_2);
		void fill_board();

		std::string to_string();
};

#endif
