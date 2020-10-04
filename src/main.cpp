#include <iostream>

#include "antlr4-runtime.h"
#include "src/lsystem/parser/LsystemLexer.h"
#include "src/lsystem/parser/LsystemParser.h"

using namespace antlr4;

int main(int argc, char** argv) {
	std::ifstream stream;
	stream.open("test.lsystem");

	ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	std::cout << "Hello world" << std::endl;
	return 0;
}
