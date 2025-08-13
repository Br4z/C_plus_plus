#include <iostream>
#include <stdexcept>

#include "Cinema.h"


Cinema::Cinema() {

}

std::string Cinema::list_movies() {
	std::string output = "";
	for (int i = 0; i < movies_length; i++)
		output += movies[i].to_string() + "\n";
	return output;
}

const Movie& Cinema::get_movie(int index) {
	if (0 > index || index >= movies_length)
		throw std::out_of_range("Error: invalid movie index");
	else
		return movies[index];
}

void Cinema::add_movie(Movie movie) {
	if (movies_length == 20)
		throw std::runtime_error("Error: maximum number of movies reached");
	else {
		movie.set_index(movies_length + 1);
		movies[movies_length++] = movie;
	}
}

void Cinema::set_basic_price_ticket(float basic_price_ticket) {
	this -> basic_price_ticket = basic_price_ticket;
}

void Cinema::add_projection_room(ProjectionRoom projection_room) {
	if (movies_length == 4)
		throw std::runtime_error("Error: maximum number of projection rooms reached");
	else
		projection_rooms[projection_rooms_length++] = projection_room;
}

std::string Cinema::search_movies_by_genre(GENRE genre) {
	std::string output = "";
	for (int i = 0; i < movies_length; i++) {
		Movie movie = movies[i];

		if (movie.get_genre() == genre)
			output += movie.to_string() + '\n';
	}
	return output;
}

std::string Cinema::consult_movie_projections(int movie_index) {
	std::string output = "";

	for (int i = 0; i < projection_rooms_length; i++) {
		ProjectionRoom projection_room = projection_rooms[i];
		int projections_length = projection_room.get_projections_length();

		for (int j = 0; j < projections_length; j++) {
			Projection projection = projection_room.get_projection(j);
			Movie movie = projection.get_movie();

			if (movie.get_index() == movie_index) {
				output += "Projection room: " + projection_room.get_name() + "\n";
				output += projection.to_string() + "\n";
			}
		}
	}
	return output;
}
