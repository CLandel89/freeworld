#include "src/mps-sp/instance.hpp"
#include "src/mps-sp/instance-private.hpp"
#include "src/mps/instance.hpp"
#include "src/sp/instance.hpp"

#ifndef RELEASE
#include <iostream> //cout
#endif
#include <stdio.h> //fopen, fclose
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

namespace Freeworld {

// internal definitions (incl. declarations)

//recursively load all .rb scripts in a directory
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

// exported definitions

InstanceMpsSp::InstanceMpsSp(InstanceMps* mps, InstanceSp* sp)
: mps(mps), sp(sp) {
	priv = new InstanceMpsSpPrivate();
	core_utils = new CoreUtils(this);
	database = new Database(this);
	integration = new Integration::IntegrationMpsSp(this);
}

InstanceMpsSp::~InstanceMpsSp() {
	delete integration;
	delete database;
	delete core_utils;
	delete priv;
}

void InstanceMpsSp::start(std::vector<std::string> vm_pkgs)
{
	integration->init();
	auto& vm = priv->vm;
	vm = mrb_open();
	database->init();
	core_utils->init();
	vm_instance_map[vm] = this;
	boost::filesystem::path dyn("./dyn/");
	rec_load(vm, dyn);

	for ( auto iter = vm_pkgs.begin();
			iter != vm_pkgs.end();
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

void InstanceMpsSp::stop() {
	core_utils->quit();
	database->quit();
	auto& vm = priv->vm;
	vm_instance_map[vm] = NULL;
	mrb_close(vm);
	vm = NULL;
	integration->quit();
}

} //end of namespace Freeworld

