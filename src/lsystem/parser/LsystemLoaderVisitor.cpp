#include "LsystemLoaderVisitor.h"

#include "../../value/Value.h"

using namespace lsystem;

antlrcpp::Any LsystemLoaderVisitor::visitLsystem(LsystemParser::LsystemContext* ctx) {
	rules = std::vector<Rule>();
	int generations = std::stoi(ctx->generations->getText());
	std::shared_ptr<Value> angle = visitNumWithDev(ctx->angle);
	std::vector<Command> initiator = visitCommands(ctx->initiator);
	std::vector<Command> leafableRule = visitCommands(ctx->leafablerule);
	visitChildren(ctx);
	return std::make_shared<Lsystem>(generations, angle, initiator, leafableRule, rules);
}

antlrcpp::Any LsystemLoaderVisitor::visitLrule(LsystemParser::LruleContext* ctx) {
	std::string name = ctx->name->getText();
	bool isLeaf = ctx->isleaf != nullptr;
	bool isLeafable = ctx->isleafable != nullptr;
	currentParentRule = name;
	currentParentRuleIsLeaf = isLeaf;
	currentParentRuleIsLeafable = isLeafable;
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
	Command cmd("F", CommandType::FORWARD); // placeholder value (will be overwritten)

	switch (ctx->getStart()->getType()) {
	case LsystemLexer::LEFT:
		cmd = Command(ctx->getText(), CommandType::YAW_LEFT);
		break;
	case LsystemLexer::RIGHT:
		cmd = Command(ctx->getText(), CommandType::YAW_RIGHT);
		break;
	case LsystemLexer::ROLL_CW:
		cmd = Command(ctx->getText(), CommandType::ROLL_CW);
		break;
	case LsystemLexer::ROLL_CCW:
		cmd = Command(ctx->getText(), CommandType::ROLL_CCW);
		break;
	case LsystemLexer::PITCH_UP:
		cmd = Command(ctx->getText(), CommandType::PITCH_UP);
		break;
	case LsystemLexer::PITCH_DOWN:
		cmd = Command(ctx->getText(), CommandType::PITCH_DOWN);
		break;
	case LsystemLexer::PUSH:
		cmd = Command(ctx->getText(), CommandType::PUSH);
		break;
	case LsystemLexer::POP:
		cmd = Command(ctx->getText(), CommandType::POP);
		break;
	case LsystemLexer::SCALE_ALL:
		cmd = Command(ctx->getText(), CommandType::SCALE_ALL);
		break;
	default:
		std::cerr << "Error no command symbol found: " << ctx->getText() << std::endl;
		exit(1);
	}

	if (ctx->arg1 != nullptr) {
		cmd.dataValue = visitNumWithDev(ctx->arg1);
	}

	currentCommands.push_back(cmd);

	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitSubruleSym(LsystemParser::SubruleSymContext* ctx) {
	if (ctx->getText() == "F") {
		currentCommands.push_back(Command(ctx->getText(), CommandType::FORWARD, currentParentRule, currentParentRuleIsLeaf, currentParentRuleIsLeafable));
	}
	else if (ctx->getText() == "f") {
		currentCommands.push_back(Command(ctx->getText(), CommandType::SKIP_FORWARD, currentParentRule, currentParentRuleIsLeaf, currentParentRuleIsLeafable));
	}
	else {
		currentCommands.push_back(Command(ctx->getText(), CommandType::ID));
	}
	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitScaleLength(LsystemParser::ScaleLengthContext* ctx) {
	std::shared_ptr<Value> scaleFactor = visitNumWithDev(ctx->value);
	currentCommands.push_back(Command(ctx->getText(), CommandType::SCALE_LENGTH, scaleFactor));
	return NULL;
}

antlrcpp::Any LsystemLoaderVisitor::visitNumWithDev(LsystemParser::NumWithDevContext* ctx) {
	std::shared_ptr<Value> value = visitNum(ctx->value);
	auto devCtx = ctx->dev;
	if (devCtx == nullptr) {
		return value;
	}
	else {
		auto dev = std::atof(devCtx->getText().c_str());
		return Value::createNormal(value->sample(), dev);
	}
}

antlrcpp::Any LsystemLoaderVisitor::visitNum(LsystemParser::NumContext* ctx) {
	return Value::createConstant(std::atof(ctx->getText().c_str()));
}

