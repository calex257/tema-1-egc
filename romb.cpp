#include "romb.h"
#include "star.h"
#include "lane.h"
#include "hexagon.h"
#include <chrono>

namespace tema {
	tema::Romb::Romb(){

	}

	tema::Romb::Romb(Mesh* mesh, int price, int type){
		this->mesh = mesh;
		this->price = price;
		this->type = type;
	}
	Romb::~Romb() {

	}
	void Romb::animate(float deltaTime) {

		if (!should_render) {
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
		should_fire = checkShouldFire();
		if (should_fire) {
			auto now = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> elapsed_seconds = now - last_fire;
			std::chrono::milliseconds secs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);

			if (secs.count() > 1000) {
				last_fire = now;
				Star* s = new Star(projectile_mesh, true, this->type);
				s->scaleBy(20);
				s->moveTo(this->position + glm::vec3(20, 0, 0));
				s->update();
				this->parent->addShape(s);
			}
			return;
		}
		last_fire = std::chrono::high_resolution_clock::now();
	}
	bool Romb::checkShouldFire() {
		const Lane* l = dynamic_cast<Lane*>(this->parent);
		if (l == nullptr) {
			return false;
		}
		for (Shape* s : l->shapes) {
			const Hexagon* hex = dynamic_cast<Hexagon*>(s);
			if (hex == nullptr) {
				continue;
			}
			if (hex->type == this->type && hex->dying == false) {
				return true;
			}
		}
		return false;
	}
	void Romb::startFiring() {
		should_fire = checkShouldFire();
		last_fire = std::chrono::high_resolution_clock::now();
	}
}
