#ifndef FREEWORLD_SQLITE_UTIL_HPP
#define FREEWORLD_SQLITE_UTIL_HPP

#include <sqlite3.h>
#include <string>
#include <sstream>

inline void ok_or_throw(std::string stage, int rc, sqlite3* sqlite3_db) {
	if (rc==SQLITE_OK) return;
	auto errmsg = sqlite3_errmsg(sqlite3_db);
	sqlite3_close(sqlite3_db);
	std::stringstream exn_msg;
	exn_msg << "SQLite returned with error " << rc << " during " << stage << ":\n"
		<< errmsg;
	throw exn_msg.str();

}

#endif // FREEWORLD_SQLITE_UTIL_HPP
