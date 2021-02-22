#pragma once

#include <memory>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemVisitor.h"

#include "../Lsystem.h"


namespace lsystem {

	/*
		ANTLR visitor for converting the AST to an Lsystem object.
	*/
	class  LsystemLoaderVisitor : public LsystemVisitor {
	public:
		/*
			Returns the parsed Lsystem.
			@param ctx The Lsystem parser context.
			@return std::shared_ptr<Lsystem> The parsed Lsystem object.
		*/
		virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext* ctx) override;
		/*
			Adds the parsed rule to the current ruleset.
			@param ctx The rule parser context.
			@return NULL (ignored value)
		*/
		virtual antlrcpp::Any visitLrule(LsystemParser::LruleContext* ctx) override;
		/*
			Returns the parsed commands.
			@param ctx The command parser context.
			@return std::vector<Command> The commands parse from this context.
		*/
		virtual antlrcpp::Any visitCommands(LsystemParser::CommandsContext* ctx) override;
		/*
			Adds a parsed symbol to the current commands.
			@param ctx The symbol context.
			@return NULL (ignored value)
		*/
		virtual antlrcpp::Any visitSym(LsystemParser::SymContext* ctx) override;
		/*
			Adds a parsed subrule symbol to the current commands.
			A subrule symbol is a symbol representing another rule (e.g. Branch, F, f, Trunk, etc.).
			@param ctx The context.
			@return NULL (ignored value)
		*/
		virtual antlrcpp::Any visitSubruleSym(LsystemParser::SubruleSymContext* ctx) override;
		/*
			Adds a scale length command to the current commands.
			@param ctx The context.
			@return NULL (ignored value)
		*/
		virtual antlrcpp::Any visitScaleLength(LsystemParser::ScaleLengthContext* ctx) override;
		/*
			Returns the parsed lsystem::Value with a standard deviation.
			@param ctx The context.
			@return lsystem::Value The parsed value with a standard deviation.
		*/
		virtual antlrcpp::Any visitNumWithDev(LsystemParser::NumWithDevContext* ctx) override;
		/*
			Returns a parsed float.
			@param ctx The context.
			@return float The parsed float value.
		*/
		virtual antlrcpp::Any visitNum(LsystemParser::NumContext* ctx) override;

	private:
		/*
			The current set of commands found while visiting the AST.
		*/
		std::vector<Command> currentCommands;
		/*
			The rules that have been currently processed from AST.
		*/
		std::vector<Rule> rules;
		/*
			The current parent rule. Used to tag output segments with geometry types.
		*/
		std::string currentParentRule = "";
		/*
			Whether the current parent rule produces a leaf (as opposed to a cylindrical segment).
		*/
		bool currentParentRuleIsLeaf = false;

};

}  // namespace lsystem
