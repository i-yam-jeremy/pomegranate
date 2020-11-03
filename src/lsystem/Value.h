#pragma once

#include <memory>

namespace lsystem {
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
		/*
			Creates a value which will always evaluate to the given constant value.
			@param c The constant value.
		*/
		Value(float c);
		/*
			Creates a value with the given mean and standard deviation.
			@param mean The mean.
			@param dev The standard deviation.
		*/
		Value(float mean, float dev);
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
};