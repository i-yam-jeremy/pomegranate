#pragma once

#include <string>
#include <vector>

#include "Command.h"

namespace lsystem {
	/*
		An Lsystem rule.
	*/
	class Rule {
	public:
		/*
			Creates a rule with the given name composed of the given commands.
			@param name The name of the rule.
			@param commands The commands in the body of this rule.
		*/
		Rule(std::string name, std::vector<Command> commands):
			name(name), 
			commands(commands) {}

		/*
			The name of this rule.
		*/
		std::string name;
		/*
			The commands in the body of this rule.
		*/
		std::vector<Command> commands;
	};
}