#include "shape.h"

namespace tema {

	Shape::Shape() {
		this->transformMatrix = glm::mat4(1.0f);
		this->scale.z = 1;
		radians = 0;
		scale = glm::vec3(1);
	}
	Shape::Shape(Mesh* mesh) {
		this->mesh = mesh;
		this->transformMatrix = glm::mat4(1.0f);
		this->scale.z = 1;
		radians = 0;
		scale = glm::vec3(1);
	}

	Shape::~Shape() {

	}
	void Shape::moveTo(glm::vec3 pos) {
		position = pos;
	}
	void Shape::rotateBy(float rads) {
		radians = rads;
	}
	void Shape::rotateBy(float rads, glm::vec3 axis) {
		rotateBy(rads);
	}
	void Shape::scaleBy(float coef) {
			scale.x = coef;
			scale.y = coef;
	}
	glm::vec3 Shape::getAbsolutePosition() {
		glm::vec3 pos = position;
		RefPointContainer* begin = parent;
		while (begin != nullptr) {
			pos += begin->position;
			begin = begin->parent;
		}
		return pos;
	}
	bool Shape::hasPointInside(int x, int y) {
		glm::vec3 pos = getAbsolutePosition();
		pos.z = 0;
		float dist = glm::distance(pos, glm::vec3(x, y, 0));
		if (dist < scale.x) {
			return true;
		}
		return false;
	}
	bool Shape::collidesWith(Shape* shape) {
		return false;
	}
	void Shape::animate(float deltaTime) {
		return;
	}
	void Shape::scaleBy(float coef, int axis) {
		switch (axis) {
		case OX:
			scale.x = coef;
			break;
		case OY:
			scale.y = coef;
			break;
		case OZ:
			scale.z = coef;
			break;
		default:
			break;
		}
	}
	void Shape::update() {
		if (!should_render) {
			transformMatrix = glm::mat4(0);
			return;
		}
		transformMatrix = glm::mat4(1);
		transformMatrix = glm::translate(transformMatrix, getAbsolutePosition());
		transformMatrix = glm::rotate(transformMatrix, radians, glm::vec3(0, 0, 1));
		transformMatrix = glm::scale(transformMatrix, scale);
	}
}
