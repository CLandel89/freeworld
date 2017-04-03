#include "src/integration/lib/mps-sp-sqlite/chunks.hpp"
#include <sstream>

#include "src/integration/lib/mps-sp-sqlite/database.hpp"

//this source file implements the following header:
#include "src/integration-headers/mps-sp/database.hpp"

namespace Freeworld { namespace Integration {

sqlite3* database;

// helper functions

void ok_or_throw(std::string stage, int rc) {
	if (rc==SQLITE_OK) return;
	auto errmsg = sqlite3_errmsg(database);
	sqlite3_close(database);
	std::stringstream exn_msg;
	exn_msg << "SQLite returned with error " << rc << " during " << stage << ":\n"
		<< errmsg;
	throw exn_msg.str();
}

// integration

void open_world(std::string world) {
	auto rc = sqlite3_open(("worlds/" + world + ".sqlite3").c_str(), &database);
	if (rc) ok_or_throw("OPEN-world", rc);
	prepare_chunks();
}

void close_world() {
	finalize_chunks();
	sqlite3_close(database);
}

} } //end of namespace Freeworld:Integration
