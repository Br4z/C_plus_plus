---
reviewed_on: "2024-09-17"
---

# Cinema

This program simulates a cinema management system. It allows users to manage movies, projection rooms, and projections. The main functionalities include adding movies, adding projection rooms, searching for movies by genre, consulting movie projections, and listing all movies.

## Functionalities

1. Add a movie.

   - Allows the user to add a new movie to the cinema's movie list.

   - The user needs to provide the movie's title and genre.

2. Add a projection room.

   - Allows the user to add a new projection room to the cinema.

   - The user needs to provide the name of the projection room.

   - The user can add up to $4$ projections to the projection room.

3. Search movies by genre.

   - Allows the user to search for movies by their genre.

   - The user needs to select a genre to see the list of movies in that genre.

4. Consult movie projections.

   - Allows the user to consult the projections of a specific movie.

   - The user needs to provide the movie index to see its projections.

5. List Movies.

   - Displays a list of all movies available in the cinema.

## Class Diagram

```mermaid
classDiagram
    class Cinema {
        -Movie movies[20]
        -int movies_length
        -float basic_price_ticket
        -ProjectionRoom projection_rooms[4]
        -int projection_rooms_length
        +Cinema()
        +list_movies() std::string
        +get_movie(int index) Movie
        +add_movie(Movie movie) void
        +set_basic_price_ticket(float basic_price_ticket) void
        +add_projection_room(ProjectionRoom projection_room) void
        +search_movies_by_genre(GENRE genre) std::string
        +consult_movie_projections(int movie_index) std::string
    }

    class Movie {
        -int movie_index
        -std::string title
        -GENRE genre
        +Movie()
        +Movie(std::string name, GENRE genre)
        +set_index(int movie_index) void
        +get_index() int
        +set_title(std::string title) void
        +get_title() std::string
        +set_genre(GENRE genre) void
        +get_genre() GENRE
        +to_string() std::string
    }

    class Projection {
        -Movie movie
        -int start_hour
        -int start_minute
        -int end_hour
        -int end_minute
        +Projection()
        +Projection(Movie movie, int start_hour, int start_minute, int end_hour, int end_minute)
        +get_movie() Movie
        +set_start_hour(int hour) void
        +get_start_hour() int
        +set_start_minute(int minute) void
        +get_start_minute() int
        +set_end_hour(int hour) void
        +get_end_hour() int
        +set_end_minute(int minute) void
        +get_end_minute() int
        +to_string() std::string
    }

    class ProjectionRoom {
        -std::string name
        -Projection projections[4]
        -int projections_length
        +ProjectionRoom()
        +ProjectionRoom(std::string name)
        +get_name() std::string
        +add_projection(Projection projection) void
        +get_projections_length() int
        +get_projection(int index) Projection
        +to_string() std::string
    }

    class GENRE {
        +ACTION
        +COMEDY
        +DRAMA
        +FANTASY
        +HORROR
        +ROMANCE
        +SCIFI
        +SUSPENSE
    }

    Cinema "1" *-- "20" Movie
    Cinema "1" *-- "4" ProjectionRoom
    ProjectionRoom "1" *-- "4" Projection
    Projection "1" *-- "1" Movie
    Movie "1" *-- "1" GENRE
```
