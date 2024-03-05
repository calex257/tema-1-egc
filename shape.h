#pragma once

#include "components/camera.h"

#include "core/world.h"
#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "core/gpu/texture2D.h"
#include "core/managers/resource_path.h"
#include "core/managers/texture_manager.h"
#include <map>

#include "utils/text_utils.h"
#include "utils/memory_utils.h"
#include "utils/gl_utils.h"
#include "utils/math_utils.h"

#include "ref_point_container.h"

#define OX 0
#define OY 1
#define OZ 2

namespace tema {

	class Shape {
	public:
		Mesh* mesh;
		glm::vec3 color;
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		glm::vec3 position;
		glm::vec3 scale = glm::vec3(1);
		float radians = 0;
		bool should_render = true;
		bool can_collide = false;
		bool dying = false;
		RefPointContainer* parent = nullptr;

		Shape();
		Shape(Mesh* mesh);
		~Shape();
		void moveTo(glm::vec3 position);
		void rotateBy(float radians);
		void rotateBy(float radians, glm::vec3 axis);
		void scaleBy(float coef);
		void scaleBy(float coef, int axis);
		virtual bool hasPointInside(int x, int y);
		virtual bool collidesWith(Shape* shape);
		virtual void animate(float deltaTime);
		glm::vec3 getAbsolutePosition();
		void update();
	};
}

