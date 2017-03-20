#ifndef DATABASE_H
#define DATABASE_H

#include <string>

namespace Freeworld { namespace Impl {

void open_world(std::string world);
void close_world();

} } //end of namespace Freeworld::Impl

#endif //DATABASE_H
