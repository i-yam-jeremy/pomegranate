
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LsystemParser.h"


namespace lsystem {

/**
 * This interface defines an abstract listener for a parse tree produced by LsystemParser.
 */
class  LsystemListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterLsystem(LsystemParser::LsystemContext *ctx) = 0;
  virtual void exitLsystem(LsystemParser::LsystemContext *ctx) = 0;

  virtual void enterLrule(LsystemParser::LruleContext *ctx) = 0;
  virtual void exitLrule(LsystemParser::LruleContext *ctx) = 0;

  virtual void enterCommands(LsystemParser::CommandsContext *ctx) = 0;
  virtual void exitCommands(LsystemParser::CommandsContext *ctx) = 0;

  virtual void enterSym(LsystemParser::SymContext *ctx) = 0;
  virtual void exitSym(LsystemParser::SymContext *ctx) = 0;

  virtual void enterSubruleSym(LsystemParser::SubruleSymContext *ctx) = 0;
  virtual void exitSubruleSym(LsystemParser::SubruleSymContext *ctx) = 0;

  virtual void enterScaleLength(LsystemParser::ScaleLengthContext *ctx) = 0;
  virtual void exitScaleLength(LsystemParser::ScaleLengthContext *ctx) = 0;

  virtual void enterNumWithDev(LsystemParser::NumWithDevContext *ctx) = 0;
  virtual void exitNumWithDev(LsystemParser::NumWithDevContext *ctx) = 0;

  virtual void enterNum(LsystemParser::NumContext *ctx) = 0;
  virtual void exitNum(LsystemParser::NumContext *ctx) = 0;


};

}  // namespace lsystem
