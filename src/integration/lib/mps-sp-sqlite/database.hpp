#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include <string>

#include <sqlite3.h>

namespace Freeworld { namespace Integration {

extern sqlite3 *database;
void ok_or_throw(std::string stage, int rc);

} } //end of namespace Freeworld::Integration


#endif // SQLITE_DATABASE_H
