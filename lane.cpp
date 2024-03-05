#include "lane.h"
#include "hexagon.h"
#include <random>
#include "utils.h"

namespace tema {
	Lane::Lane(const std::vector<Mesh*>& enemy_meshes, int chance, const glm::vec3& lane_end) : enemy_meshes(enemy_meshes), decision_maker(chance), lane_end(lane_end), last_generated_hexagon(std::chrono::high_resolution_clock::now()) {
	}
	Lane::Lane(const std::vector<Mesh*>& enemy_meshes, const glm::vec3& position, int chance, const glm::vec3& lane_end) : RefPointContainer(position), enemy_meshes(enemy_meshes), decision_maker(chance), lane_end(lane_end), last_generated_hexagon(std::chrono::high_resolution_clock::now()) {

	};
	Lane::Lane(const std::vector<Mesh*>& enemy_meshes, const glm::vec3& position, const glm::vec3& scale, int chance, const glm::vec3& lane_end) : RefPointContainer(position, scale), enemy_meshes(enemy_meshes), decision_maker(chance), lane_end(lane_end), last_generated_hexagon(std::chrono::high_resolution_clock::now()) {

	}
	void Lane::onUpdate(float deltaTime) {
		auto now = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_seconds = now - last_generated_hexagon;
		std::chrono::milliseconds secs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);

		if (secs.count() < generate_in) {
			return;
		}
		unsigned int index = decision_maker.getRandomNumber(0, (unsigned int)enemy_meshes.size());
		Hexagon* h = new Hexagon(enemy_meshes[index], 3, index);
		h->scaleBy(50);
		h->moveTo(lane_end);
		h->should_render = true;
		this->addShape(h);
		last_generated_hexagon = std::chrono::high_resolution_clock::now();
		generate_in = decision_maker.getRandomNumber(6000, 10000);
	}
}