#include "LsystemLoaderVisitor.h"

#include "../../value/Value.h"

using namespace lsystem;

antlrcpp::Any LsystemLoaderVisitor::visitLsystem(LsystemParser::LsystemContext* ctx) {
	rules = std::vector<Rule>();
	int generations = std::stoi(ctx->generations->getText());
	std::shared_ptr<Value> angle = visitNumWithDev(ctx->angle);
	int ringVertexCount = (ctx->ringvertexcount != nullptr) ?
		std::stoi(ctx->ringvertexcount->getText()) :
		16;
	float ringsPerWorldDist = (ctx->ringsperworlddist != nullptr) ?
		std::atof(ctx->ringsperworlddist->getText().c_str()) :
		0.0f;
	int minRingsPerSegment = (ctx->minringspersegment != nullptr) ?
		std::stoi(ctx->minringspersegment->getText()) :
		2;

	std::vector<Command> initiator = visitCommands(ctx->initiator);
	std::vector<Command> leafableRule;
	if (ctx->leafablerule != nullptr) {
		leafableRule = visitCommands(ctx->leafablerule).as<std::vector<Command>>();
	}
	visitChildren(ctx);
	return std::make_shared<Lsystem>(generations, angle, 
		ringVertexCount, ringsPerWorldDist, minRingsPerSegment,
		initiator, 
		leafableRule,
		rules);
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
	case LsystemLexer::SCALE_LENGTH:
		cmd = Command(ctx->getText(), CommandType::SCALE_LENGTH);
		break;
	case LsystemLexer::SCALE_ALL:
		cmd = Command(ctx->getText(), CommandType::SCALE_ALL);
		break;
	case LsystemLexer::SCALE_RADIUS:
		cmd = Command(ctx->getText(), CommandType::SCALE_RADIUS);
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

