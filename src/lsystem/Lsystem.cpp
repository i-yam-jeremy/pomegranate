#include "Lsystem.h"

#include <sstream>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include <antlr4-runtime.h>

#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"
#include "../value/Random.h"

using namespace antlr4;
using namespace lsystem;
using namespace glm;

namespace lsystem {
	class EvalState {
	public:
		EvalState() {}
		EvalState(std::shared_ptr<Value> angle) :
			mat(identity<mat4>()),
			angleChange(angle) {}

		void rotate(float yaw, float pitch, float roll) {
			yaw = radians(yaw);
			pitch = radians(pitch);
			roll = radians(roll);

			if (yaw != 0) {
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
			vec3 translateVec = vec4(1 * length, 0, 0, 0) * mat;
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
		bool dummyState = false;
	};
}

std::shared_ptr<Output> lsystem::Lsystem::compile() {
	for (int i = 0; i < floor(generations); i++) {
		state = applySingleGeneration(state, i);
	}

	float fractionalGeneration = fmod(generations, 1);
	if (fractionalGeneration != 0.0f) {
		state = applySingleGeneration(state, floor(generations), fractionalGeneration);
	}

	leafableRule = applySingleGeneration(leafableRule, 0);

	return std::make_shared<Output>(eval(state), eval(leafableRule), getRuleNames(), ringVertexCount, ringsPerWorldDist, minRingsPerSegment);
}

void lsystem::Lsystem::overrideGenerations(float generations) {
	this->generations = generations;
}

std::vector<Command> lsystem::Lsystem::applySingleGeneration(const std::vector<Command>& commands, int generation, float generationScale) {
	std::vector<Command> newCommands;
	for (const auto& cmd : commands) {
		if (cmd.type == CommandType::ID) {
			bool foundMatchingRule = false;
			for (auto& rule : rules) {
				if (rule.name == cmd.value) {
					if (generationScale != 1.0f) {
						auto newCmd = Command("", CommandType::SCALE_LENGTH);
						newCmd.dataValue = Value::createConstant(generationScale);
						newCmd.generation = generation;
						newCommands.push_back(newCmd);
					}
					for (auto cmd : rule.commands) {
						cmd.generation = generation;
						newCommands.push_back(cmd);
					}
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
	return newCommands;
}

std::shared_ptr<SingleOutput> lsystem::Lsystem::eval(std::vector<Command>& commands) {
	auto out = std::make_shared<SingleOutput>();

	std::vector<EvalState> stack;

	EvalState currentState(angle);

	for (int i = 0; i < commands.size(); i++) {
		const auto& cmd = commands[i];
		Random::setActiveGeneration(cmd.generation);
		auto& angle = (cmd.dataValue == nullptr) ? currentState.angleChange : cmd.dataValue;
		switch (cmd.type) {
		case FORWARD: {
			if (currentState.dummyState) {
				break;
			}
			auto& parent = currentState.segment;
			auto newSegment = std::make_shared<OutputSegment>(cmd.parentRuleType, currentState.mat, currentState.translation, currentState.length, parent, cmd.isLeaf, cmd.isLeafable);
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
		case SCALE_RADIUS: {
			auto scale = cmd.dataValue->sample();
			currentState.scaleLength(1.0f / scale);
			currentState.scaleUniform(scale);
			break;
		}
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
		case PUSH: {
			stack.push_back(currentState);
			if (cmd.dataValue != nullptr) {
				float branchChance = cmd.dataValue->sample();
				if (!(branchChanceCalculator->sample() < branchChance)) {
					currentState.dummyState = true;
				}
			}
			break;
		}
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

std::vector<std::string> lsystem::Lsystem::getRuleNames() {
	std::vector<std::string> names;
	for (const auto& rule : rules) {
		names.push_back(rule.name);
	}
	return names;
}

std::shared_ptr<lsystem::Output> lsystem::compile(std::string source, float overridedGenerations, bool useGenerationsOverride) {
	std::istringstream stream;
	stream.str(source);

	ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	lsystem::LsystemParser::LsystemContext* tree = parser.lsystem();

	lsystem::LsystemLoaderVisitor visitor;
	std::shared_ptr<lsystem::Lsystem> lsys = visitor.visitLsystem(tree);
	if (useGenerationsOverride) {
		lsys->overrideGenerations(overridedGenerations);
	}
	return lsys->compile();
}
