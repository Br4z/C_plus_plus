#include <string>

#ifndef MOVIE_H
#define MOVIE_H


enum class GENRE {
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
		const int& get_index() const;

		void set_title(std::string title);
		const std::string& get_title() const;

		void set_genre(GENRE genre);
		const GENRE& get_genre() const;

		std::string to_string() const;
};


#endif
