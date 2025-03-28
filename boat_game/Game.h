#include <string>

#include "Entity.h"
#include "Place.h"

#ifndef GAME_H
#define GAME_H


enum DIRECTION {
	LEFT,
	RIGHT
};

class Game {
	private:
		Place* places[4];
		Entity** entities;
		int entity_number;
		int actual_entity;
		int boat_capacity;

		bool is_prey_of(int entity_1_id, int entity_2_id) const;
		int get_entity_place(int entity_id) const;
		std::string center_text(const std::string &text, int width) const;
		int max_width_in_column(int column) const;
	public:
		Game(int additional_entities, int boat_capacity);
		~Game();

		int get_entity_number() const;

		std::string list_entities() const;
		void add_entity(std::string name);
		void add_predator_to_entity(int prey_id, int predator_id);
		std::string consult_entity(int id) const;
		std::string game_status();
		void move_entity(int entity_id, DIRECTION direction);
		void move_boat();

		std::string debug() const;
		std::string to_string() const;
};


#endif
