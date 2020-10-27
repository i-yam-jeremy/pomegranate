#pragma once

#include <string>

namespace lsystem {
	enum CommandType {
		YAW_RIGHT,
		YAW_LEFT,
		ROLL_CW,
		ROLL_CCW,
		PITCH_UP,
		PITCH_DOWN,
		PUSH,
		POP,
		FORWARD,
		SKIP_FORWARD,
		SCALE_LENGTH,
		ID
	};

	class Command {
	public:
		Command(std::string value, CommandType type, std::string parentRuleType) :
			value(value),
			type(type),
			parentRuleType(parentRuleType) {}
		Command(std::string value, CommandType type) :
			value(value),
			type(type),
			parentRuleType("") {}
		Command(std::string value, CommandType type, float dataValue) :
			value(value),
			type(type),
			parentRuleType(""),
			dataValue(dataValue) {}
		std::string value;
		CommandType type;
		std::string parentRuleType;
		float dataValue = 0;
	};
}