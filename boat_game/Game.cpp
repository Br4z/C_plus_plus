#include <iostream>
#include <stdexcept>

#include "Game.h"

Game::Game(int additional_entities, int boat_capacity) {
	this -> boat_capacity = boat_capacity;
	entity_number = 4 + additional_entities;

	places[0] = new Place("left side", entity_number);
	places[1] = new Place("boat", boat_capacity);
	places[2] = new Place("water", entity_number);
	places[3] = new Place("right side", entity_number);

	entities = new Entity*[entity_number];

	entities[0] = new Entity("robot", true, entity_number);
	entities[1] = new Entity("fox", false, entity_number);
	entities[2] = new Entity("bunny", false, entity_number);
	entities[3] = new Entity("lettuce", false, entity_number);

	places[0] -> add_entity(entities[0]);
	places[0] -> add_entity(entities[1]);
	places[0] -> add_entity(entities[2]);
	places[0] -> add_entity(entities[3]);

	entities[1] -> add_prey(entities[2]);

	entities[2] -> add_predator(entities[1]);
	entities[2] -> add_prey(entities[3]);

	entities[3] -> add_predator(entities[2]);

	actual_entity = 4;
}

Game::~Game() {
	for (int i = 0; i < 4; i++)
		delete places[i];

	for (int i = 0; i < entity_number; i++)
		delete entities[i];

	delete[] entities;
}


int Game::get_entity_number() const {
	return entity_number;
}

std::string Game::list_entities() const {
	std::string output = "Name\tID\n";
	output += "----\t--\n";

	for (int i = 0; i < actual_entity; i++) {
		Entity* entity = entities[i];

		output += entity -> get_name() + '\t' + std::to_string(entity -> get_id()) + '\n';
	}

	return output;
}

void Game::add_entity(std::string name) {
	entities[actual_entity] = new Entity(name, false, entity_number);
	places[0] -> add_entity(entities[actual_entity++]);
}

void Game::add_predator_to_entity(int prey_id, int predator_id) {
	entities[prey_id - 1] -> add_predator(entities[predator_id - 1]);
	entities[predator_id - 1] -> add_prey(entities[prey_id - 1]);
}

std::string Game::consult_entity(int id) const {
	std::string output = "";

	Entity** predators = entities[id - 1] -> get_predators();
	int predator_number = entities[id - 1] -> get_predator_number();

	output += "Predators\n";

	for (int i = 0; i < predator_number; i++) {
		Entity* entity = predators[i];

		output += "\tName: " + entity -> get_name() + " ID: " + std::to_string(entity -> get_id()) + '\n';
	}

	Entity** preys = entities[id - 1] -> get_preys();
	int prey_number = entities[id - 1] -> get_prey_number();

	output += "Preys\n";

	for (int i = 0; i < prey_number; i++) {
		Entity* entity = preys[i];

		output += "\tName: " + entity -> get_name() + " ID: " + std::to_string(entity -> get_id()) + '\n';
	}

	return output;
}

bool Game::is_prey_of(int entity_1_id, int entity_2_id) const {
	Entity** possible_predator_preys = entities[entity_2_id - 1] -> get_preys();
	int prey_number =  entities[entity_2_id - 1] -> get_prey_number();

	for (int i = 0; i < prey_number; i++)
		if (entity_1_id == possible_predator_preys[i] -> get_id())
			return true;

	return false;
}

std::string Game::game_status() {
	std::string output = "";

	/* ------------------------------- Loss cases ------------------------------- */

	for (Place* place : places) {
		if (place -> is_vigilant_there())
			continue;

		Entity** entities = place -> get_entities();
		int capacity = place -> get_capacity();

		for (int i = 0; i < capacity; i++) {
			Entity* entity = entities[i];

			if (!entity)
				continue;
			else {
				int entity_id = entity -> get_id();

				if (place -> get_name() == "water") {
					output += entity -> get_name() + " fell into the water\n";
					continue;
				}

				for (int j = 0; j < capacity; j++) {
					Entity* other_entity = entities[j];

					if (!other_entity || j == i)
						continue;

					int other_entity_id = other_entity -> get_id();

					if (is_prey_of(entity_id, other_entity_id))
						output += entities[j] -> get_name() + " eated " + entity -> get_name() + '\n';
				}
			}
		}
	}

	/* -------------------------------- Win case -------------------------------- */

	if (places[3] -> get_entity_number() == entity_number)
		output += "You won the game!";

	return output;
}

int Game::get_entity_place(int entity_id) const {
	for (int i = 0; i < 4; i++) {
		Place* place = places[i];
		Entity** entities = place -> get_entities();
		int capacity = place -> get_capacity();

		for (int j = 0; j < capacity; j++)
			if (entities[j] && entities[j] -> get_id() == entity_id)
				return i;
	}

	return -1;
}

void Game::move_entity(int entity_id, DIRECTION direction) {
	int entity_place = get_entity_place(entity_id);

	if (entity_place == -1)
		throw std::runtime_error("Error: entity not found in any place");

	int entity_index = entity_id - 1;

	if (entity_index < 0 || entity_index >= entity_number)
		throw std::runtime_error("Error: entity index out of bounds");

	if (direction == LEFT) {
		if (entity_place != 0) {
			if (places[entity_place - 1] -> get_name() != "boat" ||
				(places[entity_place - 1] -> get_name() == "boat" &&
					places[entity_place - 1] -> get_entity_number() < boat_capacity)) {
				places[entity_place] -> remove_entity(entities[entity_index]);
				places[entity_place - 1] -> add_entity(entities[entity_index]);
			}
		}
	} else {
		if (entity_place != 3) {
			if (places[entity_place + 1] -> get_name() != "boat" ||
				(places[entity_place + 1] -> get_name() == "boat" &&
					places[entity_place + 1] -> get_entity_number() < boat_capacity)) {
				places[entity_place] -> remove_entity(entities[entity_index]);
				places[entity_place + 1] -> add_entity(entities[entity_index]);
			}
		}
	}
}

void Game::move_boat() {
	if (places[1] -> get_name() == "boat" && places[1] -> is_vigilant_there()) {
		Place* temp = places[1];
		places[1] = places[2];
		places[2] = temp;
	} else if (places[2] -> get_name() == "boat" && places[2] -> is_vigilant_there()) {
		Place* temp = places[2];
		places[2] = places[1];
		places[1] = temp;
	}
}

std::string Game::debug() const {
	std::string output = "";

	for (Place* place : places)
		output += place -> to_string() + '\n';

	return output;
}

std::string Game::center_text(const std::string &text, int width) const {
	int padding = width - text.length();
	int padding_left = padding / 2;
	int padding_right = padding - padding_left;
	return std::string(padding_left, ' ') + text + std::string(padding_right, ' ');
}

int Game::max_width_in_column(int column) const {
	Place* place = places[column];
	Entity** entities = place -> get_entities();
	int capacity = place -> get_capacity();

	int max_width = (place -> get_name()).length();

	for (int i = 0; i < capacity; i++) {
		Entity* entity = entities[i];

		if (entity) {
			std::string entity_name = entity -> get_name();
			int name_length = entity_name.length();

			if (name_length > max_width)
				max_width = name_length;
		}
	}

	return max_width;
}

std::string Game::to_string() const {
	int max_widths[4] = { 0 };

	for (int i = 0; i < 4; i++)
		max_widths[i] = max_width_in_column(i);

	std::string output = "|";

	for (int i = 0; i < 4; i++)
		output += center_text(places[i] -> get_name(), max_widths[i]) + "|";

	output += '\n';

	for (int i = 0; i < entity_number; i++) {
		output += "|";
		for (int j = 0; j < 4; j++) {
			Place* place = places[j];

			if (place -> get_name() == "water") {
				output += std::string(max_widths[j], '~');
			} else {
				std::string name = "";
				Entity** entities = place -> get_entities();

				if (!(place -> get_name() == "boat" && i > boat_capacity - 1))
					if (entities[i])
						name = entities[i] -> get_name();

				output += center_text(name, max_widths[j]);
			}

			output += '|';
		}
		output += '\n';
	}

	return output;
}
