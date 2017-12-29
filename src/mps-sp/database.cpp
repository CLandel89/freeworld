#include "src/mps-sp/database.hpp"
#include "src/mps-sp/instance.hpp"
#include "src/mps-sp/instance-private.hpp"

#include <mruby.h>
//#include <mruby/compile.h>
#include <mruby/string.h>

#include "src/integration-headers/mps-sp/integration.hpp"

namespace Freeworld {

// internal definitions (incl. declarations)

mrb_value open_world_func (mrb_state* vm, mrb_value self) {
	mrb_value arg;
	mrb_get_args(vm, "S", &arg);
	vm_instance_map[vm]->integration->open_world(mrb_str_to_cstr(vm, arg));
	return mrb_nil_value();
}

mrb_value close_world_func (mrb_state* vm, mrb_value self) {
	vm_instance_map[vm]->integration->close_world();
	return mrb_nil_value();
}

mrb_value open_chunk_func (mrb_state* vm, mrb_value self) {
	mrb_value result, arg_x, arg_y, arg_z;
	mrb_get_args(vm, "iii", &arg_x, &arg_y, &arg_z);
	int32_t x = arg_x.value.i, y = arg_y.value.i, z = arg_z.value.i;
	vm_instance_map[vm]->integration->chunks->open(x,y,z);
	SET_NIL_VALUE(result);
	return result;
}

mrb_value read_chunk_func (mrb_state* vm, mrb_value self) {
	auto result = vm_instance_map[vm]->integration->chunks->read();
	return mrb_str_new(vm, (char*)(result->data), result->size);
}

// exported definitions

Database::Database(InstanceMpsSp* instance)
		: instance(instance) {
}

Database::~Database() {
}

void Database::init() {
	auto vm = instance->priv->vm;
	struct RClass* database_class = mrb_define_module(vm, "Database");
	mrb_define_class_method(vm, database_class, "open_world", &open_world_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "close_world", &close_world_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "open_chunk", &open_chunk_func, MRB_ARGS_ARG(3,0));
	mrb_define_class_method(vm, database_class, "read_chunk", &read_chunk_func, MRB_ARGS_ARG(0,0));
}

void Database::quit() {
}

} // end of namespace Freeworld
