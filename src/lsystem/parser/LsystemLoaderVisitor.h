#pragma once


#include "antlr4-runtime.h"
#include "LsystemVisitor.h"
#include "../Lsystem.h"

#include <vector>

namespace lsystem {

class  LsystemLoaderVisitor : public LsystemVisitor {
public:

	LsystemLoaderVisitor(std::vector<Command>& initiator, std::vector<Rule>& rules): initiator(initiator), rules(rules) {}

  virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSym(LsystemParser::SymContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStackCommand(LsystemParser::StackCommandContext *ctx) override {
    return visitChildren(ctx);
  }

private:
	std::vector<Command> initiator;
	std::vector<Rule> rules;

};

}  // namespace lsystem
