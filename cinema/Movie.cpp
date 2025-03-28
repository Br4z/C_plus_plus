#include "Movie.h"


Movie::Movie() {

}

Movie::Movie(std::string title, GENRE genre) {
	this -> title = title;
	this -> genre = genre;
}

void Movie::set_index(int movie_index) {
	this -> movie_index = movie_index;
}

int Movie::get_index() {
	return movie_index;
}

void Movie::set_title(std::string title) {
	this -> title = title;
}

std::string Movie::get_title() const {
	return title;
}

void Movie::set_genre(GENRE genre) {
	this -> genre = genre;
}

GENRE Movie::get_genre() const {
	return genre;
}

std::string Movie::to_string() const {
	std::string genre_string;
	switch (genre) {
		case ACTION:
			genre_string = "Action";
			break;
		case COMEDY:
			genre_string = "Comedy";
			break;
		case DRAMA:
			genre_string = "Drama";
			break;
		case FANTASY:
			genre_string = "Fantasy";
			break;
		case HORROR:
			genre_string = "Horror";
			break;
		case ROMANCE:
			genre_string = "Romance";
			break;
		case SCIFI:
			genre_string = "Sci-Fi";
			break;
		case SUSPENSE:
			genre_string = "Suspense";
			break;
		default:
			genre_string = "Unknown";
			break;
	}
	return std::to_string(movie_index) + ". Title: " + title + " Genre: " + genre_string;
}
