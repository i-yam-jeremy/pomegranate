#include "Lsystem.h"

#include <sstream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include "antlr4-runtime.h"
#include "parser/generated/LsystemLexer.h"
#include "parser/generated/LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"

using namespace antlr4;
using namespace lsystem;
using namespace glm;

namespace lsystem {
	class EvalState {
	public:
		EvalState(std::shared_ptr<Value> angle):
			mat(identity<mat4>()),
			angleChange(angle) {}

		void rotate(float yaw, float pitch, float roll) {
			yaw = radians(yaw);
			pitch = radians(pitch);
			roll = radians(roll);
			if (yaw != 0) {
				quat quaternion = glm::angleAxis(yaw, vec3(0, 0, 1));
				mat *= toMat4(quaternion);
			}
			if (pitch != 0) {
				quat quaternion = glm::angleAxis(pitch, vec3(0, 1, 0));
				mat *= toMat4(quaternion);
			}
			if (roll != 0) {
				quat quaternion = glm::angleAxis(roll, vec3(1, 0, 0));
				mat *= toMat4(quaternion);
			}
		}

		void goForward() {
			vec3 translateVec = mat * vec4(1, 0, 0, 0);
			auto translationMat = translate(identity<mat4>(), translateVec);
			mat = translationMat * mat;
		}

		void scaleLength(float factor) {
			mat = scale(mat, vec3(factor, factor, factor));
		}

	public:
		mat4 mat;
		std::shared_ptr<Value> angleChange;
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
	for (auto& cmd : state) {
		if (cmd.type == CommandType::ID) {
			bool foundMatchingRule = false;
			for (auto& rule : rules) {
				if (rule.name == cmd.value) {
					newCommands.insert(newCommands.end(), rule.commands.begin(), rule.commands.end());
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
	state = newCommands;
}

std::shared_ptr<Output> lsystem::Lsystem::eval() {
	auto out = std::make_shared<Output>();

	std::vector<EvalState> stack;

	EvalState currentState(angle);

	for (auto& cmd : state) {
		auto angle = (cmd.dataValue == nullptr) ? currentState.angleChange : cmd.dataValue;
		switch (cmd.type) {
		case FORWARD:
			out->addSegment(OutputSegment(cmd.parentRuleType, currentState.mat));
			currentState.goForward();
			break;
		case SKIP_FORWARD:
			currentState.goForward();
			break;
		case SCALE_LENGTH:
			currentState.scaleLength(cmd.dataValue->sample());
			break;
		case YAW_LEFT:
			currentState.rotate(-angle->sample(), 0, 0);
			break;
		case YAW_RIGHT:
			currentState.rotate(+angle->sample(), 0, 0);
			break;
		case PITCH_UP:
			currentState.rotate(0, -angle->sample(), 0);
			break;
		case PITCH_DOWN:
			currentState.rotate(0, +angle->sample(), 0);
			break;
		case ROLL_CW:
			currentState.rotate(0, 0, -angle->sample());
			break;
		case ROLL_CCW:
			currentState.rotate(0, 0, +angle->sample());
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
