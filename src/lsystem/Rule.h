#pragma once

#include <string>
#include <vector>

#include "Command.h"

namespace lsystem {
	class Rule {
	public:
		Rule(std::string name, std::shared_ptr<std::vector<Command>> commands):
			name(name), 
			commands(commands) {}
		std::string name;
		std::shared_ptr<std::vector<Command>> commands;
	};
}