
// Generated from C:/Users/Jeremy Berchtold/Documents/GitHub/pomegranate/src/lsystem/parser/Lsystem.g4 by ANTLR 4.8


#include "LsystemListener.h"
#include "LsystemVisitor.h"

#include "LsystemParser.h"


using namespace antlrcpp;
using namespace lsystem;
using namespace antlr4;

LsystemParser::LsystemParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

LsystemParser::~LsystemParser() {
  delete _interpreter;
}

std::string LsystemParser::getGrammarFileName() const {
  return "Lsystem.g4";
}

const std::vector<std::string>& LsystemParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& LsystemParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- LsystemContext ------------------------------------------------------------------

LsystemParser::LsystemContext::LsystemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LsystemParser::LruleContext *> LsystemParser::LsystemContext::lrule() {
  return getRuleContexts<LsystemParser::LruleContext>();
}

LsystemParser::LruleContext* LsystemParser::LsystemContext::lrule(size_t i) {
  return getRuleContext<LsystemParser::LruleContext>(i);
}

tree::TerminalNode* LsystemParser::LsystemContext::INT() {
  return getToken(LsystemParser::INT, 0);
}

LsystemParser::NumWithDevContext* LsystemParser::LsystemContext::numWithDev() {
  return getRuleContext<LsystemParser::NumWithDevContext>(0);
}

LsystemParser::CommandsContext* LsystemParser::LsystemContext::commands() {
  return getRuleContext<LsystemParser::CommandsContext>(0);
}


size_t LsystemParser::LsystemContext::getRuleIndex() const {
  return LsystemParser::RuleLsystem;
}

void LsystemParser::LsystemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLsystem(this);
}

void LsystemParser::LsystemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLsystem(this);
}


antlrcpp::Any LsystemParser::LsystemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitLsystem(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::LsystemContext* LsystemParser::lsystem() {
  LsystemContext *_localctx = _tracker.createInstance<LsystemContext>(_ctx, getState());
  enterRule(_localctx, 0, LsystemParser::RuleLsystem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
    match(LsystemParser::T__0);
    setState(17);
    match(LsystemParser::T__1);
    setState(18);
    dynamic_cast<LsystemContext *>(_localctx)->generations = match(LsystemParser::INT);
    setState(19);
    match(LsystemParser::T__2);
    setState(20);
    match(LsystemParser::T__3);
    setState(21);
    match(LsystemParser::T__1);
    setState(22);
    dynamic_cast<LsystemContext *>(_localctx)->angle = numWithDev();
    setState(23);
    match(LsystemParser::T__2);
    setState(24);
    match(LsystemParser::T__4);
    setState(25);
    match(LsystemParser::T__1);
    setState(26);
    dynamic_cast<LsystemContext *>(_localctx)->initiator = commands();
    setState(27);
    match(LsystemParser::T__2);
    setState(28);
    match(LsystemParser::T__5);
    setState(29);
    match(LsystemParser::T__6);
    setState(30);
    lrule();
    setState(35);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LsystemParser::T__2) {
      setState(31);
      match(LsystemParser::T__2);
      setState(32);
      lrule();
      setState(37);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LruleContext ------------------------------------------------------------------

LsystemParser::LruleContext::LruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LsystemParser::LruleContext::ID() {
  return getToken(LsystemParser::ID, 0);
}

LsystemParser::CommandsContext* LsystemParser::LruleContext::commands() {
  return getRuleContext<LsystemParser::CommandsContext>(0);
}


size_t LsystemParser::LruleContext::getRuleIndex() const {
  return LsystemParser::RuleLrule;
}

void LsystemParser::LruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLrule(this);
}

void LsystemParser::LruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLrule(this);
}


antlrcpp::Any LsystemParser::LruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitLrule(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::LruleContext* LsystemParser::lrule() {
  LruleContext *_localctx = _tracker.createInstance<LruleContext>(_ctx, getState());
  enterRule(_localctx, 2, LsystemParser::RuleLrule);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    dynamic_cast<LruleContext *>(_localctx)->name = match(LsystemParser::ID);
    setState(39);
    match(LsystemParser::T__1);
    setState(40);
    dynamic_cast<LruleContext *>(_localctx)->body = commands();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommandsContext ------------------------------------------------------------------

LsystemParser::CommandsContext::CommandsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LsystemParser::SymContext *> LsystemParser::CommandsContext::sym() {
  return getRuleContexts<LsystemParser::SymContext>();
}

LsystemParser::SymContext* LsystemParser::CommandsContext::sym(size_t i) {
  return getRuleContext<LsystemParser::SymContext>(i);
}

std::vector<LsystemParser::SubruleSymContext *> LsystemParser::CommandsContext::subruleSym() {
  return getRuleContexts<LsystemParser::SubruleSymContext>();
}

LsystemParser::SubruleSymContext* LsystemParser::CommandsContext::subruleSym(size_t i) {
  return getRuleContext<LsystemParser::SubruleSymContext>(i);
}

std::vector<LsystemParser::ScaleLengthContext *> LsystemParser::CommandsContext::scaleLength() {
  return getRuleContexts<LsystemParser::ScaleLengthContext>();
}

LsystemParser::ScaleLengthContext* LsystemParser::CommandsContext::scaleLength(size_t i) {
  return getRuleContext<LsystemParser::ScaleLengthContext>(i);
}


size_t LsystemParser::CommandsContext::getRuleIndex() const {
  return LsystemParser::RuleCommands;
}

void LsystemParser::CommandsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommands(this);
}

void LsystemParser::CommandsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommands(this);
}


antlrcpp::Any LsystemParser::CommandsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitCommands(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::CommandsContext* LsystemParser::commands() {
  CommandsContext *_localctx = _tracker.createInstance<CommandsContext>(_ctx, getState());
  enterRule(_localctx, 4, LsystemParser::RuleCommands);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LsystemParser::T__9)
      | (1ULL << LsystemParser::T__10)
      | (1ULL << LsystemParser::LEFT)
      | (1ULL << LsystemParser::RIGHT)
      | (1ULL << LsystemParser::ROLL_CW)
      | (1ULL << LsystemParser::ROLL_CCW)
      | (1ULL << LsystemParser::PITCH_UP)
      | (1ULL << LsystemParser::PITCH_DOWN)
      | (1ULL << LsystemParser::PUSH)
      | (1ULL << LsystemParser::POP)
      | (1ULL << LsystemParser::ID))) != 0)) {
      setState(45);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LsystemParser::LEFT:
        case LsystemParser::RIGHT:
        case LsystemParser::ROLL_CW:
        case LsystemParser::ROLL_CCW:
        case LsystemParser::PITCH_UP:
        case LsystemParser::PITCH_DOWN:
        case LsystemParser::PUSH:
        case LsystemParser::POP: {
          setState(42);
          sym();
          break;
        }

        case LsystemParser::T__9:
        case LsystemParser::ID: {
          setState(43);
          subruleSym();
          break;
        }

        case LsystemParser::T__10: {
          setState(44);
          scaleLength();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SymContext ------------------------------------------------------------------

LsystemParser::SymContext::SymContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LsystemParser::SymContext::LEFT() {
  return getToken(LsystemParser::LEFT, 0);
}

tree::TerminalNode* LsystemParser::SymContext::RIGHT() {
  return getToken(LsystemParser::RIGHT, 0);
}

tree::TerminalNode* LsystemParser::SymContext::ROLL_CW() {
  return getToken(LsystemParser::ROLL_CW, 0);
}

tree::TerminalNode* LsystemParser::SymContext::ROLL_CCW() {
  return getToken(LsystemParser::ROLL_CCW, 0);
}

tree::TerminalNode* LsystemParser::SymContext::PITCH_UP() {
  return getToken(LsystemParser::PITCH_UP, 0);
}

tree::TerminalNode* LsystemParser::SymContext::PITCH_DOWN() {
  return getToken(LsystemParser::PITCH_DOWN, 0);
}

tree::TerminalNode* LsystemParser::SymContext::PUSH() {
  return getToken(LsystemParser::PUSH, 0);
}

tree::TerminalNode* LsystemParser::SymContext::POP() {
  return getToken(LsystemParser::POP, 0);
}

LsystemParser::NumWithDevContext* LsystemParser::SymContext::numWithDev() {
  return getRuleContext<LsystemParser::NumWithDevContext>(0);
}


size_t LsystemParser::SymContext::getRuleIndex() const {
  return LsystemParser::RuleSym;
}

void LsystemParser::SymContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSym(this);
}

void LsystemParser::SymContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSym(this);
}


antlrcpp::Any LsystemParser::SymContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitSym(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::SymContext* LsystemParser::sym() {
  SymContext *_localctx = _tracker.createInstance<SymContext>(_ctx, getState());
  enterRule(_localctx, 6, LsystemParser::RuleSym);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LsystemParser::LEFT)
      | (1ULL << LsystemParser::RIGHT)
      | (1ULL << LsystemParser::ROLL_CW)
      | (1ULL << LsystemParser::ROLL_CCW)
      | (1ULL << LsystemParser::PITCH_UP)
      | (1ULL << LsystemParser::PITCH_DOWN)
      | (1ULL << LsystemParser::PUSH)
      | (1ULL << LsystemParser::POP))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(55);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LsystemParser::T__7) {
      setState(51);
      match(LsystemParser::T__7);
      setState(52);
      dynamic_cast<SymContext *>(_localctx)->arg1 = numWithDev();
      setState(53);
      match(LsystemParser::T__8);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubruleSymContext ------------------------------------------------------------------

LsystemParser::SubruleSymContext::SubruleSymContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LsystemParser::SubruleSymContext::ID() {
  return getToken(LsystemParser::ID, 0);
}


size_t LsystemParser::SubruleSymContext::getRuleIndex() const {
  return LsystemParser::RuleSubruleSym;
}

void LsystemParser::SubruleSymContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubruleSym(this);
}

void LsystemParser::SubruleSymContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubruleSym(this);
}


antlrcpp::Any LsystemParser::SubruleSymContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitSubruleSym(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::SubruleSymContext* LsystemParser::subruleSym() {
  SubruleSymContext *_localctx = _tracker.createInstance<SubruleSymContext>(_ctx, getState());
  enterRule(_localctx, 8, LsystemParser::RuleSubruleSym);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    _la = _input->LA(1);
    if (!(_la == LsystemParser::T__9

    || _la == LsystemParser::ID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScaleLengthContext ------------------------------------------------------------------

LsystemParser::ScaleLengthContext::ScaleLengthContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LsystemParser::NumWithDevContext* LsystemParser::ScaleLengthContext::numWithDev() {
  return getRuleContext<LsystemParser::NumWithDevContext>(0);
}


size_t LsystemParser::ScaleLengthContext::getRuleIndex() const {
  return LsystemParser::RuleScaleLength;
}

void LsystemParser::ScaleLengthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScaleLength(this);
}

void LsystemParser::ScaleLengthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScaleLength(this);
}


antlrcpp::Any LsystemParser::ScaleLengthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitScaleLength(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::ScaleLengthContext* LsystemParser::scaleLength() {
  ScaleLengthContext *_localctx = _tracker.createInstance<ScaleLengthContext>(_ctx, getState());
  enterRule(_localctx, 10, LsystemParser::RuleScaleLength);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(LsystemParser::T__10);
    setState(60);
    match(LsystemParser::T__7);
    setState(61);
    dynamic_cast<ScaleLengthContext *>(_localctx)->value = numWithDev();
    setState(62);
    match(LsystemParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumWithDevContext ------------------------------------------------------------------

LsystemParser::NumWithDevContext::NumWithDevContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LsystemParser::NumContext *> LsystemParser::NumWithDevContext::num() {
  return getRuleContexts<LsystemParser::NumContext>();
}

LsystemParser::NumContext* LsystemParser::NumWithDevContext::num(size_t i) {
  return getRuleContext<LsystemParser::NumContext>(i);
}


size_t LsystemParser::NumWithDevContext::getRuleIndex() const {
  return LsystemParser::RuleNumWithDev;
}

void LsystemParser::NumWithDevContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumWithDev(this);
}

void LsystemParser::NumWithDevContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumWithDev(this);
}


antlrcpp::Any LsystemParser::NumWithDevContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitNumWithDev(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::NumWithDevContext* LsystemParser::numWithDev() {
  NumWithDevContext *_localctx = _tracker.createInstance<NumWithDevContext>(_ctx, getState());
  enterRule(_localctx, 12, LsystemParser::RuleNumWithDev);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    dynamic_cast<NumWithDevContext *>(_localctx)->value = num();
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LsystemParser::T__11) {
      setState(65);
      match(LsystemParser::T__11);
      setState(66);
      dynamic_cast<NumWithDevContext *>(_localctx)->dev = num();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumContext ------------------------------------------------------------------

LsystemParser::NumContext::NumContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LsystemParser::NumContext::FLOAT() {
  return getToken(LsystemParser::FLOAT, 0);
}

tree::TerminalNode* LsystemParser::NumContext::INT() {
  return getToken(LsystemParser::INT, 0);
}


size_t LsystemParser::NumContext::getRuleIndex() const {
  return LsystemParser::RuleNum;
}

void LsystemParser::NumContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNum(this);
}

void LsystemParser::NumContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LsystemListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNum(this);
}


antlrcpp::Any LsystemParser::NumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LsystemVisitor*>(visitor))
    return parserVisitor->visitNum(this);
  else
    return visitor->visitChildren(this);
}

LsystemParser::NumContext* LsystemParser::num() {
  NumContext *_localctx = _tracker.createInstance<NumContext>(_ctx, getState());
  enterRule(_localctx, 14, LsystemParser::RuleNum);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    _la = _input->LA(1);
    if (!(_la == LsystemParser::INT

    || _la == LsystemParser::FLOAT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> LsystemParser::_decisionToDFA;
atn::PredictionContextCache LsystemParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LsystemParser::_atn;
std::vector<uint16_t> LsystemParser::_serializedATN;

std::vector<std::string> LsystemParser::_ruleNames = {
  "lsystem", "lrule", "commands", "sym", "subruleSym", "scaleLength", "numWithDev", 
  "num"
};

std::vector<std::string> LsystemParser::_literalNames = {
  "", "'generations'", "'='", "','", "'angle'", "'init'", "'rules'", "':'", 
  "'('", "')'", "'f'", "'\"'", "'dev'", "'-'", "'+'", "'\\\\'", "'/'", "'&'", 
  "'^'", "'['", "']'"
};

std::vector<std::string> LsystemParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "LEFT", "RIGHT", "ROLL_CW", 
  "ROLL_CCW", "PITCH_UP", "PITCH_DOWN", "PUSH", "POP", "ID", "INT", "FLOAT", 
  "WS"
};

dfa::Vocabulary LsystemParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> LsystemParser::_tokenNames;

LsystemParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1a, 0x4a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 
    0x2, 0x24, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x27, 0xb, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x30, 
    0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x33, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x3a, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x46, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x2, 
    0x2, 0xa, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x2, 0x5, 0x3, 0x2, 
    0xf, 0x16, 0x4, 0x2, 0xc, 0xc, 0x17, 0x17, 0x3, 0x2, 0x18, 0x19, 0x2, 
    0x47, 0x2, 0x12, 0x3, 0x2, 0x2, 0x2, 0x4, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x31, 0x3, 0x2, 0x2, 0x2, 0x8, 0x34, 0x3, 0x2, 0x2, 0x2, 0xa, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xe, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0x10, 0x47, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x7, 0x3, 0x2, 
    0x2, 0x13, 0x14, 0x7, 0x4, 0x2, 0x2, 0x14, 0x15, 0x7, 0x18, 0x2, 0x2, 
    0x15, 0x16, 0x7, 0x5, 0x2, 0x2, 0x16, 0x17, 0x7, 0x6, 0x2, 0x2, 0x17, 
    0x18, 0x7, 0x4, 0x2, 0x2, 0x18, 0x19, 0x5, 0xe, 0x8, 0x2, 0x19, 0x1a, 
    0x7, 0x5, 0x2, 0x2, 0x1a, 0x1b, 0x7, 0x7, 0x2, 0x2, 0x1b, 0x1c, 0x7, 
    0x4, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0x6, 0x4, 0x2, 0x1d, 0x1e, 0x7, 0x5, 
    0x2, 0x2, 0x1e, 0x1f, 0x7, 0x8, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x9, 0x2, 
    0x2, 0x20, 0x25, 0x5, 0x4, 0x3, 0x2, 0x21, 0x22, 0x7, 0x5, 0x2, 0x2, 
    0x22, 0x24, 0x5, 0x4, 0x3, 0x2, 0x23, 0x21, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 
    0x3, 0x2, 0x2, 0x2, 0x26, 0x3, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0x17, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x4, 
    0x2, 0x2, 0x2a, 0x2b, 0x5, 0x6, 0x4, 0x2, 0x2b, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x30, 0x5, 0x8, 0x5, 0x2, 0x2d, 0x30, 0x5, 0xa, 0x6, 0x2, 
    0x2e, 0x30, 0x5, 0xc, 0x7, 0x2, 0x2f, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2f, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x7, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x39, 0x9, 0x2, 0x2, 0x2, 0x35, 0x36, 0x7, 0xa, 0x2, 
    0x2, 0x36, 0x37, 0x5, 0xe, 0x8, 0x2, 0x37, 0x38, 0x7, 0xb, 0x2, 0x2, 
    0x38, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x39, 0x35, 0x3, 0x2, 0x2, 0x2, 0x39, 
    0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 
    0x9, 0x3, 0x2, 0x2, 0x3c, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 
    0xd, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0xa, 0x2, 0x2, 0x3f, 0x40, 0x5, 0xe, 
    0x8, 0x2, 0x40, 0x41, 0x7, 0xb, 0x2, 0x2, 0x41, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x42, 0x45, 0x5, 0x10, 0x9, 0x2, 0x43, 0x44, 0x7, 0xe, 0x2, 0x2, 
    0x44, 0x46, 0x5, 0x10, 0x9, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0xf, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 
    0x9, 0x4, 0x2, 0x2, 0x48, 0x11, 0x3, 0x2, 0x2, 0x2, 0x7, 0x25, 0x2f, 
    0x31, 0x39, 0x45, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

LsystemParser::Initializer LsystemParser::_init;
