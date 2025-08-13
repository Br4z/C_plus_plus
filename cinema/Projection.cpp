#include <stdexcept>

#include "Projection.h"


Projection::Projection() {

}

Projection::Projection(Movie movie, int start_hour,
					int start_minute, int end_hour, int end_minute) {
	if (start_hour > end_hour) {
		throw std::invalid_argument("Error: start hour is greater than end hour");
	} else if (start_hour == end_hour && start_minute > end_minute) {
		throw std::invalid_argument("Error: start minute is greater than end minute");
	} else {
		if (start_hour < 7 ||
			(start_hour == 7 && start_minute < 30))
			throw std::invalid_argument("Error: the room opens at 7:30");
		else if (start_hour > 22 ||
			(start_hour == 22 && end_minute > 30))
			throw std::invalid_argument("Error: the room closes at 22:30");
		else {
			this -> movie = movie;
			this -> start_hour = start_hour;
			this -> start_minute = start_minute;
			this -> end_hour = end_hour;
			this -> end_minute = end_minute;
		}
	}
}

const Movie& Projection::get_movie() const {
	return movie;
}

void Projection::set_start_hour(int hour) {
	start_hour = hour;
}

const int& Projection::get_start_hour() const {
	return start_hour;
}

void Projection::set_start_minute(int minute) {
	start_minute = minute;
}

const int& Projection::get_start_minute() const {
	return start_minute;
}

void Projection::set_end_hour(int hour) {
	end_hour = hour;
}

const int& Projection::get_end_hour() const {
	return end_hour;
}

void Projection::set_end_minute(int minute) {
	end_minute = minute;
}

const int& Projection::get_end_minute() const {
	return end_minute;
}

std::string Projection::to_string() const {
	std::string projection_string = "Movie: " + movie.get_title() + "\n";
	projection_string += "Start Time: " + std::to_string(start_hour) + ": " + std::to_string(start_minute) + "\n";
	projection_string += "End Time: " + std::to_string(end_hour) + ": " + std::to_string(end_minute) + "\n";
	return projection_string;
}
