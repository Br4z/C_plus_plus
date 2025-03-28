#include "Movie.h"

#ifndef PROJECTION_H
#define PROJECTION_H


class Projection {
	private:
		Movie movie;

		int start_hour;
		int start_minute;

		int end_hour;
		int end_minute;

	public:
		Projection();
		Projection(Movie movie, int start_hour, int start_hour_minute,
					int end_hour, int end_minute);

		Movie get_movie();

		void set_start_hour(int hour);
		int get_start_hour() const;

		void set_start_minute(int minute);
		int get_start_minute() const;

		void set_end_hour(int hour);
		int get_end_hour() const;

		void set_end_minute(int minute);
		int get_end_minute() const;

		std::string to_string() const;
};


#endif
