#include "Lsystem.h"

#include <sstream>

#include "antlr4-runtime.h"
#include "LsystemLexer.h"
#include "LsystemParser.h"
#include "parser/LsystemLoaderVisitor.h"

using namespace antlr4;

namespace lsystem {
class Lsystem {
public:
	Lsystem(std::string source) {
		std::istringstream stream;
		stream.str(source);

		ANTLRInputStream input(stream);
		lsystem::LsystemLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		lsystem::LsystemParser parser(&tokens);

		lsystem::LsystemParser::LsystemContext* tree = parser.lsystem();

		lsystem::LsystemLoaderVisitor visitor(initiator, rules);
		visitor.visitLsystem(tree);
	}

	std::shared_ptr<LsystemOutput> compile() {
		return std::make_shared<LsystemOutput>();
		// TODO
	}
private:
	std::vector<Command> initiator;
	std::vector<Rule> rules;
};

} // End namespace lsystem

std::shared_ptr<lsystem::LsystemOutput> lsystem::compile(std::string source) {
	lsystem::Lsystem lsys(source);
	return lsys.compile();
}
