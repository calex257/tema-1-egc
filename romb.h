#pragma once

#include "shape.h"
#include "random_number_generator.h"
#include <chrono>

namespace tema {

	class Romb : public Shape
	{
	public:
		bool should_move = false;
		bool should_fire = false;
		int price;
		int type;
		Mesh* projectile_mesh;
		std::chrono::high_resolution_clock::time_point last_fire;

		Romb();
		Romb(Mesh* mesh, int price, int type);
		~Romb();
		void animate(float deltaTime) override;
		bool checkShouldFire();
		void startFiring();
	};

}

