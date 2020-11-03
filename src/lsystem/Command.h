#pragma once

#include <string>

namespace lsystem {
	/*
		The type of an Lsystem command.
	*/
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

	/*
		A single Lsystem command.
	*/
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

		/*
			The text value of this command.
		*/
		std::string value;
		/*
			The type of this command.
		*/
		CommandType type;
		/*
			The geometry type of the parent rule of this command.
			Used to label output segments with the correct geometry type.
		*/
		std::string parentRuleType;
		/*
			The first float argument to this command.
		*/
		float dataValue = 0;
	};
}