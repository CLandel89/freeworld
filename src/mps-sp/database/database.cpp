#include "src/mps-sp/database/chunks.hpp"
#include <iostream>

#include <mruby.h>
//#include <mruby/compile.h>
#include <mruby/string.h>

#include "src/integration-headers/mps-sp/database.hpp"

namespace Freeworld {

mrb_value open_world_func (mrb_state* vm, mrb_value self);
mrb_value close_world_func (mrb_state* vm, mrb_value self);

void init_database (mrb_state* vm)
{
	struct RClass* database_class = mrb_define_module(vm, "Database");

	mrb_define_class_method(vm, database_class, "open_world", &open_world_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "close_world", &close_world_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "open_chunk", &open_chunk_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "read_chunk", &read_chunk_func, MRB_ARGS_ARG(0,0));
}

mrb_value close_world_func (mrb_state* vm, mrb_value self) {
	Freeworld::Impl::close_world();
	return mrb_nil_value();
}

mrb_value open_world_func (mrb_state* vm, mrb_value self) {
	mrb_value arg;
	mrb_get_args(vm, "S", &arg);
	Freeworld::Impl::open_world(mrb_str_to_cstr(vm, arg));
	return mrb_nil_value();
}

} // end of namespace Freeworld
