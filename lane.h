#pragma once

#include "ref_point_container.h"
#include "shape.h"
#include "random_number_generator.h"
#include <chrono>

namespace tema {
	class Lane : public RefPointContainer {
	public:
		std::vector<Mesh*> enemy_meshes;
		RandomNumberGenerator decision_maker;
		glm::vec3 lane_end;
		unsigned int generate_in;
		std::chrono::high_resolution_clock::time_point last_generated_hexagon;
		explicit Lane(const std::vector<Mesh*>& enemy_meshes, int chance, const glm::vec3& lane_end);
		explicit Lane(const std::vector<Mesh*>& enemy_meshes, const glm::vec3& position, int chance, const glm::vec3& lane_end);
		explicit Lane(const std::vector<Mesh*>& enemy_meshes, const glm::vec3& position, const glm::vec3& scale, int chance, const glm::vec3& lane_end);
		void onUpdate(float deltaTime) override;

	};
}