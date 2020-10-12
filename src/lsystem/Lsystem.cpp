#include "Lsystem.h"

#include <sstream>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"

using namespace antlr4;
using namespace lsystem;

namespace lsystem {
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
}

std::shared_ptr<Output> lsystem::Lsystem::compile() {
	for (int i = 0; i < generations; i++) {
		applySingleGeneration();
	}

	return eval();
}

void lsystem::Lsystem::applySingleGeneration() {
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

std::shared_ptr<Output> lsystem::Lsystem::eval() {
	auto out = std::make_shared<Output>();

	std::vector<EvalState> stack;

	EvalState currentState(FbxVector4(0, 0, 0, 0), FbxVector4(0, 0, 0, 0), 1.0, angle * 3.1415926535 / 180);

	for (auto cmd : *state) {
		switch (cmd.type) {
		case FORWARD: {
			auto dir = currentState.getDirection();
			out->addSegment(OutputSegment(cmd.parentRuleType, currentState.position, dir, currentState.length));
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

std::shared_ptr<lsystem::Output> lsystem::compile(std::string source) {
	std::istringstream stream;
	stream.str(source);

	ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	lsystem::LsystemParser::LsystemContext* tree = parser.lsystem();

	lsystem::LsystemLoaderVisitor visitor;
	std::shared_ptr<lsystem::Lsystem> lsys = visitor.visitLsystem(tree);
	return lsys->compile();
}
