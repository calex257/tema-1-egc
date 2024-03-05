#include "square.h"
#include "hexagon.h"

namespace tema {
	Square::Square(bool can_collide) {
		this->can_collide = can_collide;
	}
	Square::Square(Mesh* mesh, bool can_collide) {
		this->mesh = mesh;
		this->can_collide = can_collide;
	}
	Square::~Square() {

	}
	bool Square::hasPointInside(int x, int y) {
		float xlimit = scale.x;
		float ylimit = scale.y;
		glm::vec3 abs_position = getAbsolutePosition();
		float xcenter = abs_position.x;
		float ycenter = abs_position.y;
		if (x > xcenter + xlimit) return false;
		if (x < xcenter - xlimit) return false;
		if (y > ycenter + ylimit) return false;
		if (y < ycenter - ylimit) return false;
		return true;
	}
	bool Square::collidesWith(Shape* s) {
		Hexagon* h = dynamic_cast<Hexagon*>(s);
		if (h == nullptr) {
			return false;
		}
		float xlimit = scale.x;
		glm::vec3 abs_position = getAbsolutePosition();
		glm::vec3 abs_hex_position = h->getAbsolutePosition();
		float xcenter = abs_position.x;
		if (abs_hex_position.x - h->scale.x <= xcenter + xlimit) {
			return true;
		}
		return false;
	}
}