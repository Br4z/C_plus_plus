#include "Projection.h"

#ifndef PROJECTION_ROOM_H
#define PROJECTION_ROOM_H


class ProjectionRoom {
	private:
		std::string name;
		Projection projections[4];
		int projections_length = 0;
	public:
		ProjectionRoom();
		ProjectionRoom(std::string name);

		std::string get_name();
		void add_projection(Projection projection);
		int get_projections_length();
		Projection get_projection(int index) const;

		std::string to_string() const;
};


#endif
