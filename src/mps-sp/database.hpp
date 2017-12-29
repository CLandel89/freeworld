namespace Freeworld {
class Database;
}

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "src/mps-sp/instance.hpp"

namespace Freeworld {

class Database {
public:
	InstanceMpsSp* instance;
	Database(InstanceMpsSp* instance);
	~Database();
	void init();
	void quit();
};

} // end of namespace Freeworld

#endif // DATABASE_HPP
