#include "Random.h"

#include <sstream>

std::vector<std::shared_ptr<Random::RNGState>> Random::stateStack;
std::default_random_engine Random::generator = std::default_random_engine();
std::normal_distribution<float> Random::normalDist(0, 1);
std::uniform_real_distribution<float> Random::uniformDist(0, 1);

void Random::seed(long seed) {
	generator.seed(seed);
}

#include <iostream>
void Random::pushState() {
	std::cout << "PUSH" << std::endl;
	auto state = std::make_shared<RNGState>();
	std::stringstream s;
	state->generator << generator;
	state->normalDist << normalDist;
	state->uniformDist << uniformDist;
	stateStack.push_back(state);
}

void Random::popState() {
	std::cout << "POP" << std::endl;
	auto state = stateStack.back();
	stateStack.pop_back();
	state->generator >> generator;
	state->normalDist >> normalDist;
	state->uniformDist >> uniformDist;
}

float Random::evalNormal(float mean, float stddev) {
	return normalDist(generator)*stddev + mean;
}

float Random::evalUniform(float min, float max) {
	return uniformDist(generator)*(max-min) + min;
}

