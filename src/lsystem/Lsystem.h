#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <fbxsdk.h>

namespace lsystem {

class LsystemOutputSegment {
public:
	LsystemOutputSegment(std::string type, FbxVector4 startPosition, FbxVector4 direction, double length) :
		type(type),
		startPosition(startPosition),
		direction(direction),
		length(length) {}
	std::string toString() {
		return "<" + type 
			+ ", (" + std::to_string(startPosition[0]) 
			+ "," + std::to_string(startPosition[1])
			+ "," + std::to_string(startPosition[2])
			+ "), (" + std::to_string(direction[0])
			+ "," + std::to_string(direction[1])
			+ "," + std::to_string(direction[2])
			+ "), " + std::to_string(length);
	};

	std::string type;
	FbxVector4 startPosition;
	FbxVector4 direction;
	double length;
};

class LsystemOutput {
public:
	void addSegment(LsystemOutputSegment segment) {
		segments.push_back(segment);
	};

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
	Command(std::string value, CommandType type, std::string parentRuleType):
		value(value),
		type(type),
		parentRuleType(parentRuleType) {}
	Command(std::string value, CommandType type) :
		value(value),
		type(type),
		parentRuleType("") {}
	std::string value;
	CommandType type;
	std::string parentRuleType;
};

struct Rule {
	Rule(std::string name, std::shared_ptr<std::vector<Command>> commands) : name(name), commands(commands) {}
	std::string name;
	std::shared_ptr<std::vector<Command>> commands;
};

class EvalState {
public:
	EvalState(FbxVector4 position, FbxVector4 angles, double length, double angleChange) : 
		position(position), 
		angles(angles), 
		length(length),
		angleChange(angleChange) {}

	FbxVector4 getDirection() {
		return FbxVector4(cos(angles[0]), sin(angles[0]), 0, 0);
	}

public:
	FbxVector4 position;
	FbxVector4 angles;
	double length;
	double angleChange;
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
		auto out = std::make_shared<LsystemOutput>();

		std::vector<EvalState> stack;

		EvalState currentState(FbxVector4(0, 0, 0, 0), FbxVector4(0, 0, 0, 0), 1.0, 25*3.1415926535/180);

		for (auto cmd : *state) {
			switch (cmd.type) {
			case FORWARD: {
				auto dir = currentState.getDirection();
				out->addSegment(LsystemOutputSegment(cmd.parentRuleType, currentState.position, dir, currentState.length));
				currentState.position += dir * currentState.length;
				break;
			}
			case YAW_LEFT:
				currentState.angles[0] -= currentState.angleChange;
				break;
			case YAW_RIGHT:
				currentState.angles[0] += currentState.angleChange;
				break;
			case PUSH:
				stack.push_back(currentState);
				break;
			case POP:
				if (stack.size() == 0) {
					std::cerr << "Error: Attempting to pop but nothing on Lsystem eval stack" << std::endl;
					exit(1);
				}
				currentState = stack.back();
				stack.pop_back();
				break;
			}
		}

		return out;
	}

private:
	int generations;
	std::shared_ptr<std::vector<Command>> state;
	std::shared_ptr<std::vector<Rule>> rules;
};

std::shared_ptr<LsystemOutput> compile(std::string source);

} // End namespace lsystem
