#pragma once

#include <memory>

#include "antlr4-runtime.h"
#include "LsystemVisitor.h"

#include "../Lsystem.h"


namespace lsystem {

class  LsystemLoaderVisitor : public LsystemVisitor {
public:

  virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *ctx) override {
	//std::shared_ptr<std::vector<Command>> initiator = visitCommands(ctx->initiator);
	return std::make_shared<Lsystem>(std::make_shared<std::vector<Command>>(), std::make_shared<std::vector<Rule>>());
  }

  virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext *ctx) override {
	std::cout << "Reached command: " << ctx->toString() << std::endl;
	return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSym(LsystemParser::SymContext *ctx) override {
	/*switch(ctx->toString()[0]) {
		case '-':
			return Command(value, CommandType::YAW_LEFT);
		default:
			std::cerr << "Error no command symbol found" << std::endl;
			exit(1);
	}*/
	  return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStackCommand(LsystemParser::StackCommandContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace lsystem
