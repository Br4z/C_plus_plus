#include <string>

#ifndef ENTITY_H
#define ENTITY_H


class Entity {
	private:
		static int next_id;
		int id;
		std::string name;
		bool is_vigilant;

		Entity** predators;
		int predator_number;

		Entity** preys;
		int prey_number;
	public:
		Entity();
		Entity(std::string name, bool is_vigilant, int game_entities);
		~Entity();

		int get_id() const;
		std::string get_name() const;
		bool get_is_vigilant() const;

		Entity** get_predators();
		int get_predator_number() const;

		Entity** get_preys();
		int get_prey_number() const;

		void add_predator(Entity* predator);
		void add_prey(Entity* prey);
};


#endif
