#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace lsystem {

class LsystemOutputSegment {
public:
	std::string toString() {
		return "<" + type + ", (" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "), " + std::to_string(length);
	};

	std::string type;
	double x, y, z;
	double yaw, pitch, roll;
	double length;
};

class LsystemOutput {
public:
	std::string toString() {
		std::string s = "LsystemOutput {\n";
		for (auto segment : segments) {
			s += segment.toString() + "\n";
		}
		s += "}";
		return s;
	};

	std::vector<LsystemOutputSegment> segments;
};

enum CommandType {
	YAW_RIGHT,
	YAW_LEFT,
	PUSH,
	POP,
	FORWARD,
	ID
};

class Command {
public:
	Command(std::string value, CommandType type) : value(value), type(type) {}
	std::string value;
	CommandType type;	
};

struct Rule {
	Rule(std::string name, std::shared_ptr<std::vector<Command>> commands) : name(name), commands(commands) {}
	std::string name;
	std::shared_ptr<std::vector<Command>> commands;
};

class Lsystem {
public:
	Lsystem(int generations, std::shared_ptr<std::vector<Command>> initiator, std::shared_ptr<std::vector<Rule>> rules): generations(generations), state(initiator), rules(rules) {}

	std::shared_ptr<LsystemOutput> compile() {
		for (int i = 0; i < generations; i++) {
			applySingleGeneration();
		}
		
		return eval();
	}

private:
	void applySingleGeneration() {
		std::vector<Command> newCommands;
		for (auto cmd : *state) {
			if (cmd.type == CommandType::ID) {
				bool foundMatchingRule = false;
				for (auto rule : *rules) {
					if (rule.name == cmd.value) {
						newCommands.insert(newCommands.end(), rule.commands->begin(), rule.commands->end());
						foundMatchingRule = true;
						break;
					}
				}
				if (!foundMatchingRule) {
					newCommands.push_back(cmd);
				}
			}
			else {
				newCommands.push_back(cmd);
			}
		}
		*state = newCommands;
	}

	std::shared_ptr<LsystemOutput> eval() {
		return std::make_shared<LsystemOutput>(); // TODO
	}

private:
	int generations;
	std::shared_ptr<std::vector<Command>> state;
	std::shared_ptr<std::vector<Rule>> rules;
};

std::shared_ptr<LsystemOutput> compile(std::string source);

} // End namespace lsystem
