#pragma once

#include "shape.h"

namespace tema {

	class Star : public Shape {
	public:
		int type;
		Star(bool can_collide);
		Star(Mesh* mesh, bool can_collide = false, int type = -1);
		~Star();
		void animate(float deltaTime) override;
	};

}

