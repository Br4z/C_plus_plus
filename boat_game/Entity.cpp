#include <stdexcept>

#include "Entity.h"


int Entity::next_id = 1;

Entity::Entity() {

}

Entity::Entity(std::string name, bool is_vigilant, int game_entities) {
	if (next_id >= game_entities + 1)
		throw std::runtime_error("Exceeded the maximum number of game entities");
	else {
		id = next_id++;
		this -> name = name;
		this -> is_vigilant = is_vigilant;

		predators = new Entity*[game_entities];
		preys = new Entity*[game_entities];

		predator_number = 0;
		prey_number = 0;
	}
}

Entity::~Entity() {
	delete[] predators;
	delete[] preys;
}


const int& Entity::get_id() const {
	return id;
}

const std::string& Entity::get_name() const {
	return name;
}

const bool& Entity::get_is_vigilant() const {
	return is_vigilant;
}

Entity** Entity::get_predators() {
	return predators;
}

const int& Entity::get_predator_number() const {
	return predator_number;
}

Entity** Entity::get_preys() {
	return preys;
}

const int& Entity::get_prey_number() const {
	return prey_number;
}

void Entity::add_predator(Entity* predator) {
	if (predator -> get_id() == id)
		throw std::runtime_error("Error: an entity cannot be its own predator");
	predators[predator_number++] = predator;
}

void Entity::add_prey(Entity* prey) {
	if (prey -> get_id() == id)
		throw std::runtime_error("Error: an entity cannot be its own prey");
	preys[prey_number++] = prey;
}
