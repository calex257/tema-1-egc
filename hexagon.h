#pragma once

#include "shape.h"

namespace tema {

	class Hexagon : public Shape {
	public:
		int nr_of_lives;
		int type;
		Hexagon();
		Hexagon(Mesh* mesh, int nr_of_lives, int type);
		~Hexagon();
		void animate(float deltaTime) override;
		bool collidesWith(Shape* shape) override;
	};
}

