//use functions from the sp LIB
#include "../../../sp/sp.h"

int main(int argc, const char** args)
{
	std::vector<std::string> pkgs;
	pkgs.push_back("std");
	Jumpfree::Sp::start("asdf", pkgs, pkgs);
	Jumpfree::Sp::stop();
}
