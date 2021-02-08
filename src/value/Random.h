#pragma once

#include <random>
#include <unordered_map>

class Random {
public:
	static void seed(long seed);
	static void saveState(int generation);
	static void restoreState(int generation);
	static float evalNormal(float mean, float stddev);
	static float evalUniform(float min, float max);

private:
	struct RNGState {
		std::default_random_engine generator;
		std::normal_distribution<float> normalDist;
		std::uniform_real_distribution<float> uniformDist;
	};
	static std::unordered_map<int, RNGState> stateMap;
	static std::default_random_engine generator;
	static std::normal_distribution<float> normalDist;
	static std::uniform_real_distribution<float> uniformDist;
};