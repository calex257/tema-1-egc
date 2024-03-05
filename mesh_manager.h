#pragma once

#include "components/simple_scene.h"

namespace tema {
	class MeshManager {
	public:
		static Mesh* initSquareMesh(glm::vec3 color, std::string name);
		static Mesh* initSquareContourMesh(glm::vec3 color, std::string name);
		static Mesh* initStarMesh(glm::vec3 color, std::string name);
		static Mesh* initRombMesh(glm::vec3 base_color, glm::vec3 cannon_color, std::string name);
		static Mesh* initHexagonMesh(glm::vec3 color_outer, glm::vec3 color_inner, std::string name);
	
		static constexpr float HEXAGON_BORDER = 0.50f;
		static constexpr float Z_AXIS_OVERLAP = 0.05f;

	};
}