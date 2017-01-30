#include "load_vm.h"

#include <iostream> //cout
#include <stdio.h> //fopen, fclose
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <mruby.h>
#include <mruby/compile.h>

namespace Freeworld { namespace Common {

//recursively load all .rb scripts in a directory
void rec_load(mrb_state* vm, boost::filesystem::path path);

void load_vm(mrb_state* vm, std::vector<std::string> pkgs)
{
	boost::filesystem::path dyn("./dyn/");
	rec_load(vm, dyn);

	for ( auto iter = pkgs.begin();
			iter != pkgs.end();
			iter++ )
	{
#ifndef RELEASE
			std::cout << "Entering package '" << *iter << "'\n";
#endif
		boost::filesystem::path pkg("./dyn-entities/" + *iter);
		rec_load(vm, pkg);
#ifndef RELEASE
			std::cout << "Exiting package '" << *iter << "'\n";
#endif
	}
}

void rec_load(mrb_state* vm, boost::filesystem::path path)
{
	boost::regex script_pattern(".*\\.rb");
	//first only load scripts in directory...
	for (
			boost::filesystem::directory_iterator iter(path), end;
			iter != end;
			iter++ )
	{
		std::string filename = iter->path().filename().string();
		if (
				boost::filesystem::is_regular(*iter) &&
				boost::regex_match(filename, script_pattern) )
		{
#ifndef RELEASE
			std::cout << "Loading script '" << filename << "'\n";
#endif
			FILE* script_file = fopen (iter->path().c_str(), "r");
			mrb_load_file(vm, script_file);
			fclose(script_file);
		}
	}

	//then go into nested directories
	for (
			boost::filesystem::directory_iterator iter(path), end;
			iter != end;
			iter++ )
	{
		if (boost::filesystem::is_directory(iter->status())) {
#ifndef RELEASE
			std::cout << "Entering dir '" << iter->path().filename().string() << "'\n";
#endif
			rec_load(vm, *iter);
#ifndef RELEASE
			std::cout << "Exiting dir '" << iter->path().filename().string() << "'\n";
#endif
		}
	}
}

} } //end of namespace Freeworld::Common
