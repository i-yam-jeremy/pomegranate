
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LsystemVisitor.h"


namespace lsystem {

/**
 * This class provides an empty implementation of LsystemVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LsystemBaseVisitor : public LsystemVisitor {
public:

  virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSym(LsystemParser::SymContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubruleSym(LsystemParser::SubruleSymContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitScaleLength(LsystemParser::ScaleLengthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumWithDev(LsystemParser::NumWithDevContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNum(LsystemParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace lsystem
