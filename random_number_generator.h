#pragma once

#include <random>

namespace tema {
	class RandomNumberGenerator {
	public:
		unsigned int limit;
		unsigned int from;
		unsigned int to;

		explicit RandomNumberGenerator(unsigned int limit);
		bool getDecision();
		double getRandomNumber();
		unsigned int getRandomNumber(unsigned int from, unsigned int to);
	private:
	public:
		RandomNumberGenerator(unsigned int limit, unsigned int from, unsigned int to, std::seed_seq* seed);
	};
}