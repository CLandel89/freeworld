#ifndef FREEWORLD_SQLITE_HPP
#define FREEWORLD_SQLITE_HPP

#include <string>

#include <sqlite3.h>

namespace Freeworld { namespace Integration {

class IntegrationMpsSpPrivate {
public:
	sqlite3* sqlite3_db;
	IntegrationMpsSpPrivate();
	~IntegrationMpsSpPrivate();
};

} } //end of namespace Freeworld::Integration


#endif // FREEWORLD_SQLITE_HPP
