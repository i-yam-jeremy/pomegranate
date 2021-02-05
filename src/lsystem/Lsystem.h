#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Output.h"
#include "Command.h"
#include "Rule.h"

namespace lsystem {

	/*
		An Lsystem used for creating procedural geometry.
	*/
	class Lsystem {
	public:
		/*
			Creates an Lsystem from the given parameters.
			@param generations - The number of generations to apply when evaluating this Lsystem.
			@param angle - The base angle of this Lsystem.
			@param initiator - The started set of commands at generation 0.
			@param rules - The ruleset to apply each generation.
		*/
		Lsystem(int generations, std::shared_ptr<Value> angle, std::vector<Command> initiator, std::vector<Rule> rules):
			generations(generations),
			angle(angle),
			state(initiator),
			rules(rules) {}

		/*
			Compiles and evaluates the Lsystem into a structure usable for instancing procedural geometry.
			@return The evaluated Lsystem structure.
		*/
		std::shared_ptr<Output> compile();
	private:
		/*
			Applies a single generation of the Lsystem ruleset to the current state.
		*/
		void applySingleGeneration();
		/*
			Evaluates all commands in the current state into an output structure for
			instancing procedural geometry.
			@return The evaluated Lsystem structure.
		*/
		std::shared_ptr<Output> eval();

	private:
		/*
			The number of generations to apply when evaluating this Lsystem.
		*/
		int generations;
		/*
			The base angle.
		*/
		std::shared_ptr<Value> angle;
		/*
			The current ruleset state.
		*/
		std::vector<Command> state;
		/*
			The ruleset.
		*/
		std::vector<Rule> rules;
		/*
		
		*/
		std::shared_ptr<Value> branchChanceCalculator = Value::createUniform(0, 1);
	};

	std::shared_ptr<Output> compile(std::string source);

} // End namespace lsystem
