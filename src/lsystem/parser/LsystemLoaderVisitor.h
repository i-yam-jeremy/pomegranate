#pragma once

#include <memory>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemVisitor.h"

#include "../Lsystem.h"


namespace lsystem {

class  LsystemLoaderVisitor : public LsystemVisitor {
public:
	virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext* ctx) override;
	virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext* ctx) override;
	virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext* ctx) override;
	virtual antlrcpp::Any visitSym(LsystemParser::SymContext* ctx) override;
	virtual antlrcpp::Any visitSubruleSym(LsystemParser::SubruleSymContext* ctx) override;
	virtual antlrcpp::Any visitScaleLength(LsystemParser::ScaleLengthContext* ctx) override;

private:
	std::vector<Command> currentCommands;
	std::vector<Rule> rules;
	std::string currentParentRule = ""; // For determining which rule caused which forward command, so forwards within Trunk rules will become Trunk objects, etc.

};

}  // namespace lsystem
