#ifndef DATABASE_CHUNKS_H
#define DATABASE_CHUNKS_H

#include <mruby.h>

namespace Freeworld { namespace Common { namespace Database {

mrb_value open_chunk (mrb_state* vm, mrb_value self);
mrb_value read_chunk (mrb_state* vm, mrb_value self);

} } } // end of namespace Freeworld::Common::CoreUtils

#endif // DATABASE_CHUNKS_H
