#include <stdexcept>

#include "ProjectionRoom.h"


ProjectionRoom::ProjectionRoom() {

}

ProjectionRoom::ProjectionRoom(std::string name) {
	this -> name = name;
}

std::string ProjectionRoom::get_name() {
	return name;
}

void ProjectionRoom::add_projection(Projection projection) {
	if (projections_length == 4)
		throw std::runtime_error("Error: maximum number of projections reached");
	else
		projections[projections_length++] = projection;
}

int ProjectionRoom::get_projections_length() {
	return projections_length;
}

Projection ProjectionRoom::get_projection(int index) const {
	if (0 > index || index >= projections_length)
		throw std::out_of_range("Error: Invalid projection index");

	return projections[index];
}

std::string ProjectionRoom::to_string() const {
	std::string room_string = "Projection Room: " + name + "\n";
	for (int i = 0; i < projections_length; i++) {
		room_string += "Projection " + std::to_string(i + 1) + ":\n";
		room_string += projections[i].to_string() + "\n";
	}
	return room_string;
}
