#include <iostream>

#include "antlr4-runtime/antlr4-runtime.h"
#include "antlr4-runtime/LsystemLexer.h"
#include "antlr4-runtime/LsystemParser.h"

using namespace antlr4;

int main(int argc, char** argv) {
	std::ifstream stream;
	stream.open("test.lsystem");

	ANTLRInputStream input(stream);
	LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	LsystemParser parser(&tokens);

	std::cout << "Hello world" << std::endl;
	return 0;
}
