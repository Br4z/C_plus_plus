# Boat game

### Statement

The Boat Game is a puzzle where you need to transport a set of entities across a river using a boat. The boat has a limited capacity, and certain entities cannot be left together without supervision. The goal is to move all entities from the left side of the river to the right side without any entity being harmed.

### Class diagram

```mermaid
classDiagram
    class Entity {
        -int id;
        -std::string name;
        -bool is_vigilant;

        -Entity** predators;
        -int predator_number;

        -Entity** preys;
        -int prey_number;

        +int get_id() const
        +std::string get_name() const
        +bool get_is_vigilant() const

        +Entity** get_predators()
        +int get_predator_number() const

        +Entity** get_preys()
        +int get_prey_number() const

        +void add_predator(Entity* predator)
        +void add_prey(Entity* prey)
    }

    class Place {
        -std::string name;
        -Entity entities;
        -int capacity;
        -int entity_number;

        +std::string get_name() const
        +Entity** get_entities() const
        +int get_capacity() const
        +int get_entity_number() const

        +void add_entity(Entity* entity)
        +void remove_entity(Entity* entity)
        +bool is_vigilant_there() const

        +std::string to_string() const
    }

    class Game {
        -Place* places[4]
        -Entity** entities;
        -int entity_number;
        -int boat_capacity;

        -bool is_prey_of(int entity_1_id, int entity_2_id) const
        -int get_entity_place(int entity_id) const
        -std::string center_text(const std::string &text, int width) const
        -int max_width_in_column(int column) const
    
        +int get_entity_number() const
        +std::string list_entities() const
        +void add_entity(std::string name)
        +void add_predator_to_entity(int prey_id, int predator_id)
        +std::string consult_entity(int id) const
        +std::string game_status()
        +void move_entity(int entity_id, DIRECTION direction)
        +void move_boat()
        +std::string debug() const
        +std::string to_string() const
    }

    Entity "1" -- "*" Place : contains
    Place "1" -- "*" Game : manages
    Entity "1" -- "*" Game : uses
```
