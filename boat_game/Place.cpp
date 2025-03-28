#include <iostream>
#include <stdexcept>

#include "Place.h"


Place::Place() {

}

Place::Place(std::string name, int capacity) {
	this -> name = name;
	this -> capacity = capacity;
	entities = new Entity*[capacity];

	for (int i = 0; i < capacity; i++)
		entities[i] = nullptr;

	entity_number = 0;
}

Place::~Place() {
	delete[] entities;
}


std::string Place::get_name() const {
	return name;
}

Entity** Place::get_entities() const {
	return entities;
}

int Place::get_capacity() const {
	return capacity;
}

int Place::get_entity_number() const {
	return entity_number;
}

void Place::add_entity(Entity* entity) {
	if (entity_number == capacity)
		throw std::runtime_error("Error: full capacity reached");
	else
		for (int i = 0; i < capacity; i++)
			if (!entities[i]) {
				entities[i] = entity;
				entity_number++;
				break;
			}
}

void Place::remove_entity(Entity* entity) {
	for (int i = 0; i < capacity; i++)
		if (entities[i] && entities[i] -> get_id() == entity -> get_id()) {
			entities[i] = nullptr;
			entity_number--;
			break;
		}
}

bool Place::is_vigilant_there() const {
	for (int i = 0; i < capacity; i++)
		if (entities[i] && entities[i] -> get_is_vigilant()) {
			return true;
		}

	return false;
}

std::string Place::to_string() const {
	std::string output = "Place name: " + name + '\n' +
							"Capacity: " + std::to_string(capacity) + '\n' +
							"Is vigilant there: " + std::string(is_vigilant_there() ? "true" : "false") + '\n' +
							"Entity number: " + std::to_string(entity_number) + '\n' +
							"Entities:\n";


	for (int i = 0; i < capacity; i++)
		if (entities[i])
			output += "\t ID: " + std::to_string(entities[i] -> get_id()) +
						" Name: " + entities[i] -> get_name() +
						" List index: " + std::to_string(i) +
						" Memory address: " + std::to_string(reinterpret_cast<uintptr_t>(entities[i])) + '\n';

	return output;
}
