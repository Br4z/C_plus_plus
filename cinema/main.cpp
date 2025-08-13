// Reviewed on: 2025-08-12
#include <iostream>
#include <type_traits>

#include "Cinema.h"

void clear_screen() {
	std::cout << std::string(100, '\n');
}

template <typename T>
T prompt_for_numeric(const std::string &message) {
	while (true) {
		std::cout << message;
		std::string line;
		std::getline(std::cin, line);
		try {
			if constexpr (std::is_same_v <T, int>)
				return std::stoi(line);
			else if constexpr (std::is_same_v <T, float>)
				return std::stof(line);
		} catch (const std::exception &) {
			std::cerr << "Invalid input. Please enter a valid number.\n";
		}
	}
}

std::string prompt_for_string(const std::string &message) {
	std::cout << message;
	std::string line;
	std::getline(std::cin, line);
	return line;
}

/* -------------------------------------------------------------------------- */

GENRE ask_movie_genre() {
	int genre_index;
	do {
		genre_index = prompt_for_numeric <int>(
			"Enter the genre of the movie:\n"
			"1. ACTION.   2. COMEDY.   3. DRAMA.\n"
			"4. FANTASY.  5. HORROR.   6. ROMANCE.\n"
			"7. SCIFI.    8. SUSPENSE.\n-> ");
	} while (genre_index < 1 || genre_index > 8);
	return static_cast <GENRE> (genre_index - 1);
}

void add_movie(Cinema &cinema) {
	std::string name = prompt_for_string("Enter the name of the movie: ");
	GENRE genre = ask_movie_genre();
	cinema.add_movie(Movie(name, genre));
	std::cout << "\nMovie added successfully!\n";
}

void add_projection_room(Cinema &cinema) {
	std::string name = prompt_for_string("Enter the name of the new projection room: ");
	ProjectionRoom new_room(name);

	std::cout << "\nNow, add projections to '" << name << "'.\n";
	while (new_room.get_projections_length() < 4) { // Assuming a max of 4 per room
		try {
			std::cout << "\n--- Adding Projection " << new_room.get_projections_length() + 1 << " ---\n";
			std::cout << "Available Movies:\n" << cinema.list_movies() << '\n';

			int movie_index = prompt_for_numeric <int>("Enter the index of the movie to project: ");
			Movie movie = cinema.get_movie(movie_index - 1); // get_movie throws if index is bad

			int start_hour = prompt_for_numeric <int>("Enter start hour (24h): ");
			int start_minute = prompt_for_numeric <int>("Enter start minute: ");
			int end_hour = prompt_for_numeric <int>("Enter end hour (24h): ");
			int end_minute = prompt_for_numeric <int>("Enter end minute: ");

			// The Projection constructor will throw if times are invalid
			Projection projection(movie, start_hour, start_minute, end_hour, end_minute);
			new_room.add_projection(projection);

			std::cout << "Projection added successfully.\n";

			if (new_room.get_projections_length() < 4) {
				std::string add_another = prompt_for_string("Add another projection to this room? (y/n): ");
				if (add_another != "y" && add_another != "Y")
					break;
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << ". Please try again.\n";
		}
	}

	cinema.add_projection_room(new_room);
	std::cout << "\nProjection room '" << name << "' has been added to the cinema!\n";
}

void search_movies_by_genre(Cinema &cinema) {
	std::cout << "Select a genre to search for:\n";
	GENRE genre = ask_movie_genre();
	std::cout << cinema.search_movies_by_genre(genre) << '\n';
}

void consult_movie_projections(Cinema &cinema) {
	std::cout << cinema.list_movies() << '\n';
	int movie_index = prompt_for_numeric <int>("Enter the movie index to see its projections: ");
	std::cout << cinema.consult_movie_projections(movie_index) << '\n';
}

void generate_dummy_data(Cinema &cinema) {
	Movie movie_1 = Movie("Spider-Man: Far From Home", GENRE::ACTION);
	Movie movie_2 = Movie("Toy Story 4", GENRE::COMEDY);
	Movie movie_3 = Movie("The Irishman", GENRE::DRAMA);
	Movie movie_4 = Movie("Avengers: Infinity War", GENRE::FANTASY);
	Movie movie_5 = Movie("Us", GENRE::HORROR);
	Movie movie_6 = Movie("La La Land", GENRE::ROMANCE);
	Movie movie_7 = Movie("Interstellar", GENRE::SCIFI);
	Movie movie_8 = Movie("Gone Girl", GENRE::SUSPENSE);

	cinema.add_movie(movie_1);
	cinema.add_movie(movie_2);
	cinema.add_movie(movie_3);
	cinema.add_movie(movie_4);
	cinema.add_movie(movie_5);
	cinema.add_movie(movie_6);
	cinema.add_movie(movie_7);
	cinema.add_movie(movie_8);

	ProjectionRoom room_1("Room 1");
	ProjectionRoom room_2("Room 2");
	ProjectionRoom room_3("Room 3");

	Projection projection_1(cinema.get_movie(0), 10, 0, 12, 0);
	Projection projection_2(cinema.get_movie(1), 14, 0, 16, 0);
	Projection projection_3(cinema.get_movie(2), 18, 0, 21, 0);
	Projection projection_4(cinema.get_movie(3), 10, 0, 13, 0);
	Projection projection_5(cinema.get_movie(4), 15, 0, 17, 0);
	Projection projection_6(cinema.get_movie(5), 19, 0, 21, 0);
	Projection projection_7(cinema.get_movie(6), 12, 0, 15, 0);
	Projection projection_8(cinema.get_movie(7), 16, 0, 18, 0);

	room_1.add_projection(projection_1);
	room_1.add_projection(projection_2);
	room_2.add_projection(projection_3);
	room_2.add_projection(projection_4);
	room_3.add_projection(projection_5);
	room_3.add_projection(projection_6);
	room_3.add_projection(projection_7);
	room_3.add_projection(projection_8);

	cinema.add_projection_room(room_1);
	cinema.add_projection_room(room_2);
	cinema.add_projection_room(room_3);
}

int main() {
	Cinema cinema;

	float basic_price = prompt_for_numeric <float>("Enter the basic ticket price: ");
	cinema.set_basic_price_ticket(basic_price);

	generate_dummy_data(cinema);
	clear_screen();

	const std::string menu =
		"========================\n"
		"  Welcome to the Cinema\n"
		"========================\n"
		"1. Add a movie.\n"
		"2. Add a projection room.\n"
		"3. List all movies.\n"
		"4. Search movies by genre.\n"
		"5. Consult movie projections.\n"
		"6. Exit.\n"
		"-> ";

	while (true) {
		int option = prompt_for_numeric <int>(menu);
		clear_screen();

		if (option == 6) {
			std::cout << "Thank you for visiting!\n";
			break;
		}

		switch (option) {
			case 1:
				add_movie(cinema);
				break;
			case 2:
				add_projection_room(cinema);
				break;
			case 3:
				std::cout << "--- All Movies ---\n" << cinema.list_movies() << '\n';
				break;
			case 4:
				search_movies_by_genre(cinema);
				break;
			case 5:
				consult_movie_projections(cinema);
				break;
			default:
				std::cout << "Invalid option. Please try again.\n";
				break;
		}
		prompt_for_string("\nPress Enter to continue...");
		clear_screen();
	}

	return 0;
}
