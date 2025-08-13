#include "Movie.h"


Movie::Movie() {

}

Movie::Movie(std::string title, GENRE genre)
	: title(std::move(title)), genre(genre) { }

void Movie::set_index(int movie_index) {
	this -> movie_index = movie_index;
}

const int& Movie::get_index() const {
	return movie_index;
}

void Movie::set_title(std::string title) {
	this -> title = title;
}

const std::string& Movie::get_title() const {
	return title;
}

void Movie::set_genre(GENRE genre) {
	this -> genre = genre;
}

const GENRE& Movie::get_genre() const {
	return genre;
}

std::string Movie::to_string() const {
	std::string genre_string;
	switch (genre) {
		case GENRE::ACTION:
			genre_string = "Action";
			break;
		case GENRE::COMEDY:
			genre_string = "Comedy";
			break;
		case GENRE::DRAMA:
			genre_string = "Drama";
			break;
		case GENRE::FANTASY:
			genre_string = "Fantasy";
			break;
		case GENRE::HORROR:
			genre_string = "Horror";
			break;
		case GENRE::ROMANCE:
			genre_string = "Romance";
			break;
		case GENRE::SCIFI:
			genre_string = "Sci-Fi";
			break;
		case GENRE::SUSPENSE:
			genre_string = "Suspense";
			break;
		default:
			genre_string = "Unknown";
			break;
	}
	return std::to_string(movie_index) + ". Title: " + title + " Genre: " + genre_string;
}
