#include "Lsystem.h"

#include <sstream>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"

using namespace antlr4;

std::shared_ptr<lsystem::LsystemOutput> lsystem::compile(std::string source) {
	std::istringstream stream;
	stream.str(source);

	ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	lsystem::LsystemParser::LsystemContext* tree = parser.lsystem();

	lsystem::LsystemLoaderVisitor visitor;
	std::shared_ptr<lsystem::Lsystem> lsys = visitor.visitLsystem(tree);
	return lsys->compile();
}
