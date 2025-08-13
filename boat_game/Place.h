#include <string>

#include "Entity.h"

#ifndef PLACE_H
#define PLACE_H


class Place {
	protected:
		std::string name;
		Entity** entities;
		int capacity;
		int entity_number;
	public:
		Place();
		Place(std::string name, int capacity);
		~Place();

		const std::string& get_name() const;
		Entity** get_entities() const;
		const int& get_capacity() const;
		const int& get_entity_number() const;

		void add_entity(Entity* entity);
		void remove_entity(Entity* entity);
		bool is_vigilant_there() const;

		std::string to_string() const;
};


#endif
