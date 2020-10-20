#include "Lsystem.h"

#include <sstream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"

using namespace antlr4;
using namespace lsystem;
using namespace glm;

namespace lsystem {
	class EvalState {
	public:
		EvalState():
			mat(identity<mat4>()) {}

		void rotate(float yaw, float pitch, float roll) {
			/*quat quaternion = glm::angleAxis(yaw, vec3(mat[0][0], mat[1][0], mat[2][0]));
			mat *= toMat4(quaternion);

			quaternion = glm::angleAxis(pitch, vec3(mat[0][1], mat[1][1], mat[2][1]));
			mat *= toMat4(quaternion);

			quaternion = glm::angleAxis(roll, vec3(mat[0][2], mat[1][2], mat[2][2]));
			mat *= toMat4(quaternion);*/
		}

		void goForward() {
			vec3 translateVec = mat * vec4(1, 0, 0, 1);
			std::cout << "----------------" << std::endl;
			for (int m = 0; m < 4; m++) {
				for (int n = 0; n < 4; n++) {
					std::cout << mat[m][n] << ", ";
				}
				std::cout << std::endl;
			}
			std::cout << "---" << std::endl;
			mat = translate(mat, translateVec);
			for (int m = 0; m < 4; m++) {
				for (int n = 0; n < 4; n++) {
					std::cout << mat[m][n] << ", ";
				}
				std::cout << std::endl;
			}
		}

	public:
		mat4 mat;
		float angleChange;
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

	EvalState currentState;

	for (auto cmd : *state) {
		switch (cmd.type) {
		case FORWARD: {
			out->addSegment(OutputSegment(cmd.parentRuleType, currentState.mat));
			currentState.goForward();
			break;
		}
		case YAW_LEFT:
			currentState.rotate(-currentState.angleChange, 0, 0);
			break;
		case YAW_RIGHT:
			currentState.rotate(+currentState.angleChange, 0, 0);
			break;
		case PITCH_UP:
			currentState.rotate(0, -currentState.angleChange, 0);
			break;
		case PITCH_DOWN:
			currentState.rotate(0, +currentState.angleChange, 0);
			break;
		case ROLL_CW:
			currentState.rotate(0, 0, -currentState.angleChange);
			break;
		case ROLL_CCW:
			currentState.rotate(0, 0, +currentState.angleChange);
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
