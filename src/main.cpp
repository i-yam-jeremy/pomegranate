#include <iostream>
#include <sstream>

/*#include "antlr4-runtime.h"
#include "src/lsystem/parser/LsystemLexer.h"
#include "src/lsystem/parser/LsystemParser.h"*/

//using namespace antlr4;

int main(int argc, char** argv) {
	std::istringstream stream;
	stream.str("4");

	/*ANTLRInputStream input(stream);
	lsystem::LsystemLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	lsystem::LsystemParser parser(&tokens);

	lsystem::LsystemParser::LsystemContext* tree = parser.Lsystem();

	LsystemVisitor visitor;
	Lsystem* lsystem = visitor.visitLsystem(tree);
*/	
	std::cout << "Hello world" << std::endl;
	return 0;
}
