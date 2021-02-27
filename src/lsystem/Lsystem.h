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
			@param ringVertexCount - The number of vertices per ring in the output geometry.
			@param ringsPerWorldDist - The number of rings per 1 unit of world space to add to each segment in the output geometry.
			@param minRingsPerSegment - The minimum number of rings per segment in the output geometry. Rings per segment will never go below this value.
			@param initiator - The started set of commands at generation 0.
			@param leafableRule - The rule that is instanced whenever a leafable state is reached.
			@param rules - The ruleset to apply each generation.
		*/
		Lsystem(int generations, std::shared_ptr<Value> angle, int ringVertexCount, float ringsPerWorldDist, int minRingsPerSegment, std::vector<Command> initiator, std::vector<Command> leafableRule, std::vector<Rule> rules):
			generations(generations),
			angle(angle),
			ringVertexCount(ringVertexCount),
			ringsPerWorldDist(ringsPerWorldDist),
			minRingsPerSegment(minRingsPerSegment),
			state(initiator),
			leafableRule(leafableRule),
			rules(rules) {}

		/*
			Compiles and evaluates the Lsystem into a structure usable for instancing procedural geometry.
			@return The evaluated Lsystem structure.
		*/
		std::shared_ptr<Output> compile();
		/*
			Overrides the given number of generations with the new value provided.
			@param generations The value to set the number of generations to.
		*/
		void overrideGenerations(float generations);
	private:
		/*
			Applies a single generation of the Lsystem ruleset to the given set of commands.
			@param generation The index of the generation to create. Used for tagging commands.
			@param generationScale The length scale of this generation. Used for animating growth.
			@return The new command list after the generation has been applied.
		*/
		std::vector<Command> applySingleGeneration(const std::vector<Command>& commands, int generation, float generationScale = 1.0f);
		/*
			Evaluates all commands given into an output structure for
			instancing procedural geometry.
			@param commands The commands to evaluate.
			@return The evaluated Lsystem structure.
		*/
		std::shared_ptr<SingleOutput> eval(std::vector<Command>& commands);

	private:
		/*
			Returns the names of all rules.
			@return The name of each rule.
		*/
		std::vector<std::string> getRuleNames();
		/*
			The number of generations to apply when evaluating this Lsystem.
			If the value is fractional, then ceil(generations) 
			generations are applied and the last generation's length is scaled by fractional part
		*/
		float generations;
		/*
			The base angle.
		*/
		std::shared_ptr<Value> angle;
		/*
			The number of vertices per ring in the output geometry.
		*/
		int ringVertexCount;
		/*
			The number of rings per 1 unit of world space to add to each segment in the output geometry.
		*/
		float ringsPerWorldDist;
		/*
			The minimum number of rings per segment in the output geometry. Rings per segment will never go below this value.
		*/
		int minRingsPerSegment;
		/*
			The current ruleset state.
		*/
		std::vector<Command> state;
		/*
			The rule to be applied whenever a leafable state is reached.
		*/
		std::vector<Command> leafableRule;
		/*
			The ruleset.
		*/
		std::vector<Rule> rules;
		/*
		
		*/
		std::shared_ptr<Value> branchChanceCalculator = Value::createUniform(0, 1);
	};

	std::shared_ptr<Output> compile(std::string source, float overridedGenerations=1, bool useOverridedGenerations=false);

} // End namespace lsystem
