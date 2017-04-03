#ifndef DATABASE_CHUNKS_H
#define DATABASE_CHUNKS_H

#include <mruby.h>

namespace Freeworld {

mrb_value open_chunk_func (mrb_state* vm, mrb_value self);
mrb_value read_chunk_func (mrb_state* vm, mrb_value self);

} // end of namespace Freeworld

#endif // DATABASE_CHUNKS_H
