#include <string>

#ifndef MOVIE_H
#define MOVIE_H


enum GENRE {
	ACTION,
	COMEDY,
	DRAMA,
	FANTASY,
	HORROR,
	ROMANCE,
	SCIFI,
	SUSPENSE
};

class Movie {
	private:
		int movie_index;
		std::string title;
		GENRE genre;

	public:
		Movie();
		Movie(std::string name, GENRE genre);

		void set_index(int movie_index);
		int get_index();

		void set_title(std::string title);
		std::string get_title() const;

		void set_genre(GENRE genre);
		GENRE get_genre() const;

		std::string to_string() const;
};


#endif
