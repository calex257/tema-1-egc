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


namespace tema {
	class Shape;

	class RefPointContainer {
	public:
		glm::vec3 position = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);
		std::vector<RefPointContainer *> children;
		std::vector<tema::Shape *> shapes;
		RefPointContainer* parent = nullptr;

		RefPointContainer();
		explicit RefPointContainer(glm::vec3 position);
		explicit RefPointContainer(glm::vec3 position, glm::vec3 scale);
		~RefPointContainer();
		void moveTo(const glm::vec3& newpos);
		void scaleBy(float by);
		void addChildContainer(RefPointContainer* child);
		void addShape(tema::Shape* sh);
		virtual void onUpdate(float deltaTime);
	};
}