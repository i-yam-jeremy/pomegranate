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

class UniformRNG : public RNG {
public:
	UniformRNG(float min, float max) :
		min(min),
		max(max) {};

	float sample() {
		return Random::evalUniform(min, max);
	}

private:
	float min, max;
};

class NormalRNG : public RNG {
public:
	NormalRNG(float mean, float stddev) :
		mean(mean),
		stddev(stddev) {};

	float sample() {
		return Random::evalNormal(mean, stddev);
	}

private:
	float mean, stddev;
};

std::shared_ptr<Value> Value::createConstant(float c) {
	auto value = std::make_shared<Value>();
	value->rng = std::make_unique<ConstantRNG>(c);
	return value;
}

std::shared_ptr<Value> Value::createUniform(float min, float max) {
	auto value = std::make_shared<Value>();
	value->rng = std::make_unique<UniformRNG>(min, max);
	return value;
}

std::shared_ptr<Value> Value::createNormal(float mean, float dev) {
	auto value = std::make_shared<Value>();
	value->rng = std::make_unique<NormalRNG>(mean, dev);
	return value;
}

float Value::sample() {
	return rng->sample();
}