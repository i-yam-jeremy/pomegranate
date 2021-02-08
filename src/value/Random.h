#pragma once

#include <random>
#include <sstream>
#include <memory>

class Random {
public:
	static void seed(long seed);
	static void pushState();
	static void popState();
	static float evalNormal(float mean, float stddev);
	static float evalUniform(float min, float max);

private:
	struct RNGState {
		std::stringstream generator;
		std::stringstream normalDist;
		std::stringstream uniformDist;
	};
	static std::vector<std::shared_ptr<RNGState>> stateStack;
	static std::default_random_engine generator;
	static std::normal_distribution<float> normalDist;
	static std::uniform_real_distribution<float> uniformDist;
};