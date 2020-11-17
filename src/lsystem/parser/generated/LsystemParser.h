
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace lsystem {


class  LsystemParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, LEFT = 13, RIGHT = 14, 
    ROLL_CW = 15, ROLL_CCW = 16, PITCH_UP = 17, PITCH_DOWN = 18, PUSH = 19, 
    POP = 20, ID = 21, INT = 22, FLOAT = 23, WS = 24
  };

  enum {
    RuleLsystem = 0, RuleLrule = 1, RuleCommands = 2, RuleSym = 3, RuleSubruleSym = 4, 
    RuleScaleLength = 5, RuleNumWithDev = 6, RuleNum = 7
  };

  LsystemParser(antlr4::TokenStream *input);
  ~LsystemParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class LsystemContext;
  class LruleContext;
  class CommandsContext;
  class SymContext;
  class SubruleSymContext;
  class ScaleLengthContext;
  class NumWithDevContext;
  class NumContext; 

  class  LsystemContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *generations = nullptr;;
    LsystemParser::NumWithDevContext *angle = nullptr;;
    LsystemParser::CommandsContext *initiator = nullptr;;
    LsystemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LruleContext *> lrule();
    LruleContext* lrule(size_t i);
    antlr4::tree::TerminalNode *INT();
    NumWithDevContext *numWithDev();
    CommandsContext *commands();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LsystemContext* lsystem();

  class  LruleContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    LsystemParser::CommandsContext *body = nullptr;;
    LruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    CommandsContext *commands();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LruleContext* lrule();

  class  CommandsContext : public antlr4::ParserRuleContext {
  public:
    CommandsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SymContext *> sym();
    SymContext* sym(size_t i);
    std::vector<SubruleSymContext *> subruleSym();
    SubruleSymContext* subruleSym(size_t i);
    std::vector<ScaleLengthContext *> scaleLength();
    ScaleLengthContext* scaleLength(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommandsContext* commands();

  class  SymContext : public antlr4::ParserRuleContext {
  public:
    LsystemParser::NumWithDevContext *arg1 = nullptr;;
    SymContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT();
    antlr4::tree::TerminalNode *RIGHT();
    antlr4::tree::TerminalNode *ROLL_CW();
    antlr4::tree::TerminalNode *ROLL_CCW();
    antlr4::tree::TerminalNode *PITCH_UP();
    antlr4::tree::TerminalNode *PITCH_DOWN();
    antlr4::tree::TerminalNode *PUSH();
    antlr4::tree::TerminalNode *POP();
    NumWithDevContext *numWithDev();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SymContext* sym();

  class  SubruleSymContext : public antlr4::ParserRuleContext {
  public:
    SubruleSymContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubruleSymContext* subruleSym();

  class  ScaleLengthContext : public antlr4::ParserRuleContext {
  public:
    LsystemParser::NumWithDevContext *value = nullptr;;
    ScaleLengthContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumWithDevContext *numWithDev();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScaleLengthContext* scaleLength();

  class  NumWithDevContext : public antlr4::ParserRuleContext {
  public:
    LsystemParser::NumContext *value = nullptr;;
    LsystemParser::NumContext *dev = nullptr;;
    NumWithDevContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NumContext *> num();
    NumContext* num(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumWithDevContext* numWithDev();

  class  NumContext : public antlr4::ParserRuleContext {
  public:
    NumContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *INT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumContext* num();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace lsystem
