#pragma once

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
	Lsystem(std::shared_ptr<std::vector<Command>> initiator, std::shared_ptr<std::vector<Rule>> rules): initiator(initiator), rules(rules) {}

	std::shared_ptr<LsystemOutput> compile() {
		return std::make_shared<LsystemOutput>();
		// TODO
	}
private:
	std::shared_ptr<std::vector<Command>> initiator;
	std::shared_ptr<std::vector<Rule>> rules;
};

std::shared_ptr<LsystemOutput> compile(std::string source);

} // End namespace lsystem
