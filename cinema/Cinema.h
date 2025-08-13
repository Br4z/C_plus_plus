#include "Movie.h"
#include "ProjectionRoom.h"

#ifndef CINEMA_H
#define CINEMA_H


class Cinema {
	private:
		Movie movies[20];
		int movies_length = 0;
		float basic_price_ticket;
		ProjectionRoom projection_rooms[4];
		int projection_rooms_length = 0;
	public:
		Cinema();

		std::string list_movies();
		const Movie& get_movie(int index);
		void add_movie(Movie movie);
		void set_basic_price_ticket(float basic_price_ticket);
		void add_projection_room(ProjectionRoom projection_room);
		std::string search_movies_by_genre(GENRE genre);
		std::string consult_movie_projections(int movie_index);
};


#endif
