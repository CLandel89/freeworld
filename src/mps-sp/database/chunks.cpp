#include "src/mps-sp/database/chunks.hpp"

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

#include "src/integration-headers/mps-sp/chunks.hpp"

namespace Freeworld {

mrb_value open_chunk_func (mrb_state* vm, mrb_value self) {
	mrb_value result, arg_x, arg_y, arg_z;
	mrb_get_args(vm, "iii", &arg_x, &arg_y, &arg_z);
	int32_t x = arg_x.value.i, y = arg_y.value.i, z = arg_z.value.i;
	Freeworld::Integration::open_chunk(x,y,z);
	SET_NIL_VALUE(result);
	return result;
}

mrb_value read_chunk_func (mrb_state* vm, mrb_value self) {
	auto result = Freeworld::Integration::read_chunk();
	return mrb_str_new(vm, (char*)(result->data), result->size);
}

} // end of namespace Freeworld
