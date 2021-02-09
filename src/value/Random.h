#pragma once

#include <random>
#include <unordered_map>

class Random {
public:
	static void seed(long seed);
	static void setActiveGeneration(int generation);
	static float evalNormal(float mean, float stddev);
	static float evalUniform(float min, float max);

private:
	static long getCurrentIndex();

	static std::unordered_map<int, unsigned long> stateMap;
	static long baseSeed;
	static int activeGeneration;
	static std::default_random_engine generator;
	static std::normal_distribution<float> normalDist;
	static std::uniform_real_distribution<float> uniformDist;
};