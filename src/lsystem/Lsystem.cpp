#include "Lsystem.h"

#include <sstream>
#include <memory>
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

float getang(vec3 a, vec3 b) {
	return acos(dot(normalize(a), normalize(b))) * 180 / 3.14159265358;
}

bool isOrthogonal(mat4 m) {
	float epsilon = 0.001;
	vec3 b1 = vec3(m[0][0], m[0][1], m[0][2]);
	vec3 b2 = vec3(m[1][0], m[1][1], m[1][2]);
	vec3 b3 = vec3(m[2][0], m[2][1], m[2][2]);
	bool b (abs(dot(b1, b2)) < epsilon && abs(dot(b2, b3)) < epsilon && abs(dot(b3, b1)) < epsilon);
	if (!b) {
		std::cout << getang(b1, b2) << ", " << getang(b2, b3) << ", " << getang(b3, b1) << std::endl;
	}
	return b;
}

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
				/*mat4 rotM = glm::rotate(identity<mat4>(), yaw, vec3(0, 0, 1));
				for (int m = 0; m < 4; m++) {
					for (int n = 0; n < 4; n++) {
						std::cout << rotM[n][m];
						if (!(m == 3 && n == 3)) {
							std::cout << ",";
						}
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;*/
				mat = glm::rotate(identity<mat4>(), yaw, vec3(0, 0, 1)) * mat;
			}
			if (pitch != 0) {
				mat = glm::rotate(identity<mat4>(), pitch, vec3(0, 1, 0)) * mat;
			}
			if (roll != 0) {
				mat = glm::rotate(identity<mat4>(), roll, vec3(1, 0, 0)) * mat;
			}
		}

		void goForward() {
			vec3 translateVec = vec4(1*length, 0, 0, 0) * mat;
			translation += translateVec;
		}

		void scaleUniform(float s) {
			mat = scale(mat, vec3(s));
		}

		void scaleLength(float factor) {
			length *= factor;
		}

	public:
		float length = 1.0;
		vec3 translation = vec3(0);
		mat4 mat;
		std::shared_ptr<Value> angleChange;
		std::shared_ptr<OutputSegment> segment = nullptr;
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
		case FORWARD: {
			auto parent = currentState.segment;
			auto newSegment = std::make_shared<OutputSegment>(cmd.parentRuleType, currentState.mat, currentState.translation, currentState.length, parent);
			if (parent != nullptr) {
				parent->children.push_back(newSegment);
			}
			out->addSegment(newSegment);
			currentState.goForward();
			currentState.segment = newSegment;
			break;
		}
		case SKIP_FORWARD:
			currentState.goForward();
			break;
		case SCALE_LENGTH:
			currentState.scaleLength(cmd.dataValue->sample());
			break;
		case SCALE_ALL:
			currentState.scaleUniform(cmd.dataValue->sample());
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
