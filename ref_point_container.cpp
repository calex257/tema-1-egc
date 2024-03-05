#include "ref_point_container.h"
#include "shape.h"

namespace tema {
	RefPointContainer::RefPointContainer() = default;
	RefPointContainer::~RefPointContainer() = default;
	RefPointContainer::RefPointContainer(glm::vec3 pos) : position(pos) {
	}
	RefPointContainer::RefPointContainer(glm::vec3 position, glm::vec3 scale) : position(position), scale(scale) {
	}
	void RefPointContainer::moveTo(const glm::vec3& newpos) {
		this->position = newpos;
	}
	void RefPointContainer::scaleBy(float by) {
		scale += by;
	}
	void RefPointContainer::addChildContainer(RefPointContainer* child) {
		child->parent = this;
		children.emplace_back(child);
	}
	void RefPointContainer::addShape(tema::Shape* sh) {
		sh->parent = this;
		shapes.emplace_back(sh);
	}
	void RefPointContainer::onUpdate(float deltaTime) {
		
	}
}