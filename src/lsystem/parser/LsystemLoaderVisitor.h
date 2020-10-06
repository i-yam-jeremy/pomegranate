#pragma once

#include <memory>

#include "antlr4-runtime.h"
#include "LsystemVisitor.h"

#include "../Lsystem.h"


namespace lsystem {

class  LsystemLoaderVisitor : public LsystemVisitor {
public:

  virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *ctx) override {
	rules = std::make_shared<std::vector<Rule>>();
	std::shared_ptr<std::vector<Command>> initiator = visitCommands(ctx->initiator);
	visitChildren(ctx);
	return std::make_shared<Lsystem>(initiator, rules);
  }

  virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext *ctx) override {
	  std::string name = ctx->name->getText();
	  std::shared_ptr<std::vector<Command>> body = visitCommands(ctx->body);
	  rules->push_back(Rule(name, body));
	  return NULL;
  }

  virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext *ctx) override {
	  currentCommands = std::make_shared<std::vector<Command>>();
	  visitChildren(ctx);
	  return currentCommands;
  }

  virtual antlrcpp::Any visitSym(LsystemParser::SymContext *ctx) override {
	switch(ctx->getText()[0]) {
		case '-':
			currentCommands->push_back(Command(ctx->getText(), CommandType::YAW_LEFT));
			break;
		case '+':
			currentCommands->push_back(Command(ctx->getText(), CommandType::YAW_RIGHT));
			break;
		case '[':
			currentCommands->push_back(Command(ctx->getText(), CommandType::PUSH));
			break;
		case ']':
			currentCommands->push_back(Command(ctx->getText(), CommandType::POP));
			break;
		default:
			std::cerr << "Error no command symbol found: " << ctx->getText() << std::endl;
			exit(1);
	}
	return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubruleSym(LsystemParser::SubruleSymContext* ctx) override {
	  currentCommands->push_back(Command(ctx->getText(), CommandType::ID));
	  return NULL;
  }

private:
	std::shared_ptr<std::vector<Command>> currentCommands;
	std::shared_ptr<std::vector<Rule>> rules;

};

}  // namespace lsystem
