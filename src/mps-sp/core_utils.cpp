#include "src/mps-sp/core_utils.hpp"
#include "src/mps-sp/instance-private.hpp"

#include <cstring>
#ifndef RELEASE
#  include <iostream>
#endif
#include <fstream>
#include <sstream>

#include <boost/asio.hpp>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

#include "src/mpc-mps-sp/utils.hpp"

namespace Freeworld {

// internal definitions incl. declarations

/** @brief Loads the list in the specified file as MRuby constants. */
mrb_value add_enum_func (mrb_state* vm, mrb_value self) {
	mrb_value name;
	mrb_value file;
	mrb_get_args(vm, "SS", &name, &file);
	const char* name_cstr = mrb_str_to_cstr(vm, name);
	const char* file_cstr = mrb_str_to_cstr(vm, file);
#ifndef RELEASE
	std::cout << "Loading enum " << name_cstr << " from " << file_cstr << "\n";
#endif
	std::ifstream is(file_cstr);
	std::stringstream ss;
	ss << "module " << name_cstr << "\n" << is.rdbuf() << "\nend\n";
	auto eval_orig_str = ss.str();
	auto eval_orig = eval_orig_str.c_str();
	auto eval_len = strlen(eval_orig);
	char* eval = new char[eval_len + 1];
	memcpy(eval, eval_orig, eval_len + 1);
	//replace all commas by semicolons in the "eval" script
	auto eval_read = eval_len; eval_read = 0;
	while (eval[eval_read]) {
		if (eval[eval_read] == ',')
			eval[eval_read] = ';';
		eval_read++;
	}
	mrb_load_string(vm, eval);
	delete eval;
	return mrb_nil_value();
}

/** @brief Exports a delay, using boost::asio::deadline_timer.wait(), to MRuby. */
mrb_value sleep_func (mrb_state* vm, mrb_value self) {
	static boost::asio::io_service io_service;
	mrb_value seconds_raw;
	mrb_get_args(vm, "f", &seconds_raw);
	auto seconds = seconds_raw.value.f;
	//taken from: http://www.boost.org/doc/libs/1_59_0/doc/html/boost_asio/reference/deadline_timer.html
	boost::asio::deadline_timer timer(io_service);
	timer.expires_from_now(boost::posix_time::milliseconds((int)(seconds*1000)));
	timer.wait();
	return mrb_nil_value();
}

/** @brief Exports Freeworld::string_hash() to MRuby. */
mrb_value string_hash_func (mrb_state* vm, mrb_value self) {
	mrb_value result, arg;
	mrb_get_args(vm, "S", &arg);
	result.value.i = Freeworld::string_hash(mrb_str_to_cstr(vm, arg));
	result.tt = MRB_TT_FIXNUM;
	return result;
}

// exported definitions

CoreUtils::CoreUtils(InstanceMpsSp* instance)
		: instance(instance) {
}

CoreUtils::~CoreUtils() {
}

void CoreUtils::init() {
	auto vm = instance->priv->vm;
	struct RClass* core_utils_class = mrb_define_module(vm, "CoreUtils");
	mrb_define_class_method(vm, core_utils_class, "add_enum", &add_enum_func, MRB_ARGS_ARG(2,0));
	mrb_define_class_method(vm, core_utils_class, "sleep", &sleep_func, MRB_ARGS_ARG(1,0));
	mrb_define_class_method(vm, core_utils_class, "string_hash", &string_hash_func, MRB_ARGS_ARG(1,0));
}

void CoreUtils::quit() {
}

} // end of namespace Freeworld
