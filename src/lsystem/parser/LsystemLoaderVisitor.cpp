#include "LsystemLoaderVisitor.h"

using namespace lsystem;

antlrcpp::Any LsystemLoaderVisitor::visitLsystem(LsystemParser::LsystemContext* ctx) {
	rules = std::vector<Rule>();
	int generations = std::stoi(ctx->generations->getText());
	double angle = std::stod(ctx->angle->getText());
	std::vector<Command> initiator = visitCommands(ctx->initiator);
	visitChildren(ctx);
	return std::make_shared<Lsystem>(generations, angle, initiator, rules);
}

antlrcpp::Any LsystemLoaderVisitor::visitLrule(LsystemParser::LruleContext* ctx) {
	std::string name = ctx->name->getText();
	currentParentRule = name;
	std::vector<Command> body = visitCommands(ctx->body);
	rules.push_back(Rule(name, body));
	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitCommands(LsystemParser::CommandsContext* ctx) {
	currentCommands = std::vector<Command>();
	visitChildren(ctx);
	return currentCommands;
}

antlrcpp::Any LsystemLoaderVisitor::visitSym(LsystemParser::SymContext* ctx) {
	switch (ctx->getStart()->getType()) {
	case LsystemLexer::LEFT:
		currentCommands.push_back(Command(ctx->getText(), CommandType::YAW_LEFT));
		break;
	case LsystemLexer::RIGHT:
		currentCommands.push_back(Command(ctx->getText(), CommandType::YAW_RIGHT));
		break;
	case LsystemLexer::ROLL_CW:
		currentCommands.push_back(Command(ctx->getText(), CommandType::ROLL_CW));
		break;
	case LsystemLexer::ROLL_CCW:
		currentCommands.push_back(Command(ctx->getText(), CommandType::ROLL_CCW));
		break;
	case LsystemLexer::PITCH_UP:
		currentCommands.push_back(Command(ctx->getText(), CommandType::PITCH_UP));
		break;
	case LsystemLexer::PITCH_DOWN:
		currentCommands.push_back(Command(ctx->getText(), CommandType::PITCH_DOWN));
		break;
	case LsystemLexer::PUSH:
		currentCommands.push_back(Command(ctx->getText(), CommandType::PUSH));
		break;
	case LsystemLexer::POP:
		currentCommands.push_back(Command(ctx->getText(), CommandType::POP));
		break;
	default:
		std::cerr << "Error no command symbol found: " << ctx->getText() << std::endl;
		exit(1);
	}
	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitSubruleSym(LsystemParser::SubruleSymContext* ctx) {
	if (ctx->getText() == "F") {
		currentCommands.push_back(Command(ctx->getText(), CommandType::FORWARD, currentParentRule));
	}
	else if (ctx->getText() == "f") {
		currentCommands.push_back(Command(ctx->getText(), CommandType::SKIP_FORWARD, currentParentRule));
	}
	else {
		currentCommands.push_back(Command(ctx->getText(), CommandType::ID));
	}
	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitScaleLength(LsystemParser::ScaleLengthContext* ctx) {
	float scaleFactor = std::atof(ctx->value->getText().c_str());
	currentCommands.push_back(Command(ctx->getText(), CommandType::SCALE_LENGTH, scaleFactor));
	return NULL;
}

