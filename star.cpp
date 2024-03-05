#include "star.h"

namespace tema {
	Star::Star(bool can_collide) : Shape(nullptr) {
		this->can_collide = can_collide;
	}
	Star::Star(Mesh* mesh, bool can_collide, int type): Shape(mesh) {
		this->can_collide = can_collide;
		this->mesh = mesh;
		this->type = type;
	}
	Star::~Star() {

	}
	void Star::animate(float deltaTime) {
		if (!can_collide) {
			return;
		}
		if (dying) {
			scale.x -= 10 * (deltaTime >= 1 ? 1 : deltaTime);
			scale.y -= 10 * (deltaTime >= 1 ? 1 : deltaTime);
			if (scale.x < 0) {
				should_render = false;
			}
			return;
		}
		position.x += 60 * deltaTime;
		radians -= deltaTime * 20;
	}
}