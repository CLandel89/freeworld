#include <iostream>
#include <exception>

//use functions from the sp LIB
#include "src/sp/sp.hpp"

int main(int argc, const char** args)
{
	std::vector<std::string> pkgs;
	pkgs.push_back("std");
	try {
		Freeworld::start("asdf", pkgs, pkgs);
	} catch (const std::string& e) {
		std::cout << "Freeworld threw an exception:\n" << e << std::endl;
	} catch (const int& e) {
		std::cout << "Freeworld threw an exception: " << e << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Freeworld threw an exception:\n" << e.what() << std::endl;
	} catch (...) {
		auto msg = "Freeworld threw an unhandled exception.";
		std::cout << msg << std::endl;
	}
	Freeworld::stop();
}
