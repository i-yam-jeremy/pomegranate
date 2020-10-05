#pragma once

#include <string>
#include <memory>
#include <vector>

namespace lsystem {

class LsystemOutputSegment {
public:
	std::string type;
	double x, y, z;
	double yaw, pitch, roll;
	double length;
};

class LsystemOutput {
public:
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
	std::string value;
	CommandType type;	
};

struct Rule {
	std::string name;
	std::vector<Command> commands;
};

std::shared_ptr<LsystemOutput> compile(std::string source);

} // End namespace lsystem
