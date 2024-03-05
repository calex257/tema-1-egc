#pragma once
#include "shape.h"

namespace tema {

	class Square : public Shape{
	public:
		Square(bool can_collide);
		Square(Mesh* mesh, bool can_collide = false);
		~Square();
		bool hasPointInside(int x, int y) override;
		bool collidesWith(Shape* s) override;
	};
}

