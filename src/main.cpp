#include <iostream>
#include <string>
#include <sstream>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "lsystem/parser/LsystemExecutorVisitor.h"

using namespace antlr4;

int main(int argc, char** argv) {
	std::istringstream stream;
	stream.str("4");

	ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	lsystem::LsystemParser::LsystemContext* tree = parser.lsystem();

	lsystem::LsystemExecutorVisitor visitor;
	std::string lsys = visitor.visitLsystem(tree);

	std::cout << "Value: " << lsys << std::endl;
	
	std::cout << "Hello world" << std::endl;
	return 0;
}
