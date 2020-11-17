
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LsystemListener.h"


namespace lsystem {

/**
 * This class provides an empty implementation of LsystemListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LsystemBaseListener : public LsystemListener {
public:

  virtual void enterLsystem(LsystemParser::LsystemContext * /*ctx*/) override { }
  virtual void exitLsystem(LsystemParser::LsystemContext * /*ctx*/) override { }

  virtual void enterLrule(LsystemParser::LruleContext * /*ctx*/) override { }
  virtual void exitLrule(LsystemParser::LruleContext * /*ctx*/) override { }

  virtual void enterCommands(LsystemParser::CommandsContext * /*ctx*/) override { }
  virtual void exitCommands(LsystemParser::CommandsContext * /*ctx*/) override { }

  virtual void enterSym(LsystemParser::SymContext * /*ctx*/) override { }
  virtual void exitSym(LsystemParser::SymContext * /*ctx*/) override { }

  virtual void enterSubruleSym(LsystemParser::SubruleSymContext * /*ctx*/) override { }
  virtual void exitSubruleSym(LsystemParser::SubruleSymContext * /*ctx*/) override { }

  virtual void enterScaleLength(LsystemParser::ScaleLengthContext * /*ctx*/) override { }
  virtual void exitScaleLength(LsystemParser::ScaleLengthContext * /*ctx*/) override { }

  virtual void enterNumWithDev(LsystemParser::NumWithDevContext * /*ctx*/) override { }
  virtual void exitNumWithDev(LsystemParser::NumWithDevContext * /*ctx*/) override { }

  virtual void enterNum(LsystemParser::NumContext * /*ctx*/) override { }
  virtual void exitNum(LsystemParser::NumContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace lsystem
