#include "Value.h"

#include <random>
#include <iostream>

class ConstantRNG : public lsystem::RNG {
public:
	ConstantRNG(float c) {
		value = c;
	}

	float sample() {
		return value;
	}

private:
	float value;
};

class NormalRNG : public lsystem::RNG {
public:
	NormalRNG(float mean, float stddev) {
		dist = std::normal_distribution<float>(mean, stddev);
	}

	float sample() {
		return dist(generator);
	}

private:
	std::normal_distribution<float> dist;
	std::default_random_engine generator;
};

lsystem::Value::Value(float c) {
	rng = std::make_unique<ConstantRNG>(c);
}

lsystem::Value::Value(float mean, float dev) {
	rng = std::make_unique<NormalRNG>(mean, dev);
}

float lsystem::Value::sample() {
	return rng->sample();
}