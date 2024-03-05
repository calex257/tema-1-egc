#include "random_number_generator.h"

namespace tema {
	RandomNumberGenerator::RandomNumberGenerator(unsigned int limit) :limit(limit) {

	}
	RandomNumberGenerator::RandomNumberGenerator(unsigned int limit, unsigned int from, unsigned int to, std::seed_seq* seed)
		: limit(limit), from(from), to(to){
	}
	bool RandomNumberGenerator::getDecision() {
		int nr = getRandomNumber(0, limit);
		return nr == 1;
	}
	double RandomNumberGenerator::getRandomNumber() {
		static std::default_random_engine rng;

		std::uniform_real_distribution<double> dist(0.0, 0.99);
		return dist(rng);
	}
	unsigned int RandomNumberGenerator::getRandomNumber(unsigned int from, unsigned int to) {
		double num = getRandomNumber();

		return (int)(num * (to - from)) + from;
	}
}

