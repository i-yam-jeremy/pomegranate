#pragma once

#include <string>
#include <memory>

#include "../value/Value.h"

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
		SCALE_ALL,
		ID
	};

	/*
		A single Lsystem command.
	*/
	class Command {
	public:
		Command(std::string value, CommandType type, std::string parentRuleType, bool isLeaf, bool isLeafable) :
			value(value),
			type(type),
			parentRuleType(parentRuleType),
			isLeaf(isLeaf),
			isLeafable(isLeafable) {};
		Command(std::string value, CommandType type) :
			value(value),
			type(type),
			parentRuleType("") {};
		Command(std::string value, CommandType type, std::shared_ptr<Value> dataValue) :
			value(value),
			type(type),
			parentRuleType(""),
			dataValue(dataValue) {};

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
			Whether this command should produce a leaf piece of geometry (as opposed to a cylindrical segment).
		*/
		bool isLeaf = false;
		/*
			Whether this command is leafable (will auto-add leaves if a segment produced by this command has no children)
		*/
		bool isLeafable = false;
		/*
			The first float argument to this command.
		*/
		std::shared_ptr<Value> dataValue = nullptr;
		/*
			The generation this command was created on.
		*/
		int generation = -1;
	};
}