#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Output.h"
#include "Command.h"
#include "Rule.h"

namespace lsystem {

class Lsystem {
public:
	Lsystem(int generations, double angle, std::shared_ptr<std::vector<Command>> initiator, std::shared_ptr<std::vector<Rule>> rules):
		generations(generations),
		angle(angle),
		state(initiator),
		rules(rules) {}

	std::shared_ptr<Output> compile();
private:
	void applySingleGeneration();
	std::shared_ptr<Output> eval();

private:
	int generations;
	double angle;
	std::shared_ptr<std::vector<Command>> state;
	std::shared_ptr<std::vector<Rule>> rules;
};

std::shared_ptr<Output> compile(std::string source);

} // End namespace lsystem
