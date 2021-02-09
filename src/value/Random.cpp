#include "Random.h"

std::unordered_map<int, unsigned long> Random::stateMap;
long Random::baseSeed = 0L;
int Random::activeGeneration = 0;
std::default_random_engine Random::generator = std::default_random_engine();
std::normal_distribution<float> Random::normalDist(0, 1);
std::uniform_real_distribution<float> Random::uniformDist(0, 1);

void Random::seed(long seed) {
	baseSeed = seed;
}

void Random::setActiveGeneration(int generation) {
	activeGeneration = generation;
}

long Random::getCurrentIndex() {
	const auto data = stateMap.find(activeGeneration);
	if (data == stateMap.end()) {
		stateMap[activeGeneration] = 0;
	}
	return (data == stateMap.end()) ? 0 : data->second;
}

float Random::evalNormal(float mean, float stddev) {
	normalDist.reset();
	generator.seed(baseSeed + 40000L * activeGeneration + getCurrentIndex());
	return normalDist(generator)*stddev + mean;
}

float Random::evalUniform(float min, float max) {
	uniformDist.reset();
	generator.seed(baseSeed + 40000L * activeGeneration + getCurrentIndex());
	return uniformDist(generator)*(max-min) + min;
}

