#include <iostream>
#include <memory>

#include "lsystem/Lsystem.h"

int main(int argc, char** argv) {
	std::string source = "F,Trunk=F[---F][+++F]Trunk";
	std::shared_ptr<lsystem::LsystemOutput> out = lsystem::compile(source);
	std::cout << out->toString() << std::endl;
	std::cout << "Hello world" << std::endl;
	return 0;
}
