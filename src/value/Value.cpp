#include "Value.h"

#include <random>
#include <iostream>

#include "Random.h"

class ConstantRNG : public RNG {
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

class NormalRNG : public RNG {
public:
	NormalRNG(float mean, float stddev) {
		dist = std::normal_distribution<float>(mean, stddev);
	}

	float sample() {
		return dist(Random::generator);
	}

private:
	std::normal_distribution<float> dist;
};

Value::Value(float c) {
	rng = std::make_unique<ConstantRNG>(c);
}

Value::Value(float mean, float dev) {
	rng = std::make_unique<NormalRNG>(mean, dev);
}

float Value::sample() {
	return rng->sample();
}