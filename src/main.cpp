#include <iostream>
#include <memory>

#include "io/io.h"
#include "lsystem/Lsystem.h"

int main(int argc, char** argv) {
	std::string path = "C:/Users/Jeremy Berchtold/Documents/test-input.fbx";
	auto modelPieces = IO::loadInputFbx(path);

	std::string source = "2, Trunk,Trunk=F[---F][+++F]TrunkBranch, Branch = FF[-F][+F]";
	std::cout << "Source: " << source << std::endl;
	std::shared_ptr<lsystem::Output> out = lsystem::compile(source);
	std::cout << out->toString() << std::endl;
	return 0;
}
