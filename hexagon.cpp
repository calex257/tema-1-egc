#include "hexagon.h"
#include "square.h"
#include "star.h"
#include "romb.h"

namespace tema{
	Hexagon::Hexagon() {
		this->can_collide = true;
	}
	Hexagon::Hexagon(Mesh* mesh, int nr_of_lives, int type) {
		this->mesh = mesh;
		this->nr_of_lives = nr_of_lives;
		this->can_collide = true;
		this->type = type;
	}
	Hexagon::~Hexagon() {

	}

	void Hexagon::animate(float deltaTime) {
		if (!should_render) {
			return;
		}
		if (nr_of_lives <= 0) {
			dying = true;
		}
		if (dying) {
			scale.x -= 10 * (deltaTime >= 1 ? 1 : deltaTime);
			scale.y -= 10 * (deltaTime >= 1 ? 1 : deltaTime);
			if (scale.x < 0) {
				should_render = false;
			}
			return;
		}
		position.x -= 60 * deltaTime;
	}

	bool Hexagon::collidesWith(Shape* shape) {
		if (shape == nullptr) {
			return false;
		}

		if (dying) {
			return false;
		}
		Square* h = dynamic_cast<Square*>(shape);
		
		if (h != nullptr) {
			return h->collidesWith(this);
		}

		if (shape->dying) {
			return false;
		}
		
		if (!shape->can_collide) {
			return false;
		}

		Star* star_ptr = dynamic_cast<Star*>(shape);
		if (star_ptr != nullptr && star_ptr->type != this->type) {
			return false;
		}
		glm::vec3 abs_pos_me = getAbsolutePosition();
		glm::vec3 pos_me = glm::vec3(abs_pos_me.x, abs_pos_me.y, 0);
		glm::vec3 abs_pos_other = shape->getAbsolutePosition();
		glm::vec3 pos_other = glm::vec3(abs_pos_other.x, abs_pos_other.y, 0);

		float dist = glm::distance(pos_me, pos_other);
		if (dist < scale.x + shape->scale.x) {
			return true;
		}
		return false;
	}

}
