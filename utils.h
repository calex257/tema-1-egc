#pragma once

#include <string>
#include <algorithm>
#include <random>

std::string random_string(size_t length) {
	auto randchar = []() -> char {
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

//std::seed_seq  getRandomSeed() {
//	std::random_device source;
//
//	unsigned int random_data[5];
//	for (auto& elem : random_data) {
//		elem = source();
//	}
//
//	return std::seed_seq(random_data + 0, random_data + 5);
//}
//
//double randomnumber() {
//	static auto seed = getRandomSeed();
//	static std::default_random_engine rng(seed);
//
//	std::uniform_real_distribution<double> dist(0.0, 1.0);
//	return dist(rng);
//}
//double randomnumber(int from, int to) {
//	double num = randomnumber();
//
//	return (int)(num * (to - from)) + from;
//}