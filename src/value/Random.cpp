#include "Random.h"

std::unordered_map<int, Random::RNGState> Random::stateMap;
std::default_random_engine Random::generator = std::default_random_engine();
std::normal_distribution<float> Random::normalDist(0, 1);
std::uniform_real_distribution<float> Random::uniformDist(0, 1);

void Random::seed(long seed) {
	generator.seed(seed);
}

#include <iostream>
void Random::saveState(int generation) {
	std::cout << "PUSH" << std::endl;
	RNGState state;
	state.generator = generator;
	state.normalDist = normalDist;
	state.uniformDist = uniformDist;
	stateMap[generation] = state;
}

void Random::restoreState(int generation) {
	std::cout << "POP" << std::endl;
	auto state = stateMap[generation];
	state.generator = generator;
	state.normalDist = normalDist;
	state.uniformDist = uniformDist;
}

float Random::evalNormal(float mean, float stddev) {
	return normalDist(generator)*stddev + mean;
}

float Random::evalUniform(float min, float max) {
	return uniformDist(generator)*(max-min) + min;
}

