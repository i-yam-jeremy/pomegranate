
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LsystemParser.h"


namespace lsystem {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by LsystemParser.
 */
class  LsystemVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LsystemParser.
   */
    virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *context) = 0;

    virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext *context) = 0;

    virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext *context) = 0;

    virtual antlrcpp::Any visitSym(LsystemParser::SymContext *context) = 0;

    virtual antlrcpp::Any visitSubruleSym(LsystemParser::SubruleSymContext *context) = 0;

    virtual antlrcpp::Any visitScaleLength(LsystemParser::ScaleLengthContext *context) = 0;

    virtual antlrcpp::Any visitNumWithDev(LsystemParser::NumWithDevContext *context) = 0;

    virtual antlrcpp::Any visitNum(LsystemParser::NumContext *context) = 0;


};

}  // namespace lsystem
