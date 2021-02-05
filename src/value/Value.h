#pragma once

#include <memory>

/*
	An abstract class for random number generators.
*/
class RNG {
public:
	/*
		Returns a randomly sampled value on this distribution.
		@return A random value sampled according to this distribution.
	*/
	virtual float sample() = 0;
};


/*
	A numeric value that can include randomness.
*/
class Value {
public:
	Value() {};
	/*
		Creates a value which will always evaluate to the given constant value.
		@param c The constant value.
		@return The value object.
	*/
	static std::shared_ptr<Value> createConstant(float c);
	/*
		Creates a uniformally-distributed value with the given minimum and maximum values.
		@param min The minimum possible value.
		@param max The maximum possible value.
		@return The value object.
	*/
	static std::shared_ptr<Value> createUniform(float min, float max);
	/*
		Creates a normally-distributed value with the given mean and standard deviation.
		@param mean The mean.
		@param dev The standard deviation.
		@return The value object.
	*/
	static std::shared_ptr<Value> createNormal(float mean, float dev);
	/*
		Returns a randomly sampled value on this value's distribution.
		@return A random value sampled according to this value's parameters.
	*/
	float sample();
private:
	/*
		The random distribution of this value.
	*/
	std::unique_ptr<RNG> rng;
};