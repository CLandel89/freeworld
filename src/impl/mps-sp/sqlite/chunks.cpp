#include "chunks.h"
#include "database.h"

//this source file implements the following header:
#include <src/impl-headers/mps-sp/chunks.h>

namespace Freeworld { namespace Impl {

// internal workings

// private data and functions

sqlite3_stmt* open_read_stmt;
BinData* lastData = NULL;
void delete_lastData() {
	if (lastData==NULL) return;
	//this is done by SQLite:
	//if (lastData->size) delete lastData->data;
	delete lastData;
}

// module-wide data and functions

void prepare_chunks() {
	auto rc = sqlite3_prepare_v2(database,
			"SELECT data FROM chunks WHERE x=? AND y=? AND z=?", -1,
			&open_read_stmt, NULL);
	ok_or_throw("PREPARE-chunks", rc);
}

void finalize_chunks() {
	auto rc = sqlite3_finalize(open_read_stmt);
	ok_or_throw("FINALIZE-chunks", rc);
	delete_lastData();
}

// integration

int last_row_result;
void open_chunk(int32_t x, int32_t y, int32_t z) {
//	std::cout << x + ", " + y + ", " + z;
	auto rc = sqlite3_reset(open_read_stmt);
	ok_or_throw("RESET-chunks", rc);
	rc = sqlite3_bind_int(open_read_stmt, 1, x);
	ok_or_throw("BIND-chunks", rc);
	rc = sqlite3_bind_int(open_read_stmt, 2, y);
	ok_or_throw("BIND-chunks", rc);
	rc = sqlite3_bind_int(open_read_stmt, 3, z);
	ok_or_throw("BIND-chunks", rc);
	rc = sqlite3_step(open_read_stmt);
	if (rc!=SQLITE_ROW && rc!=SQLITE_DONE)
		ok_or_throw("STEP-chunks", rc);
	last_row_result = rc;
}

BinData* read_chunk() {
	delete_lastData();
	lastData = new BinData;
	if (last_row_result == SQLITE_ROW) {
		lastData->data = (uint8_t*)sqlite3_column_blob(open_read_stmt, 0);
		lastData->size = (int32_t)sqlite3_column_bytes(open_read_stmt, 0);
		//as longs as no incremental blob stuff is implemented here, we
		//can complete a chunk like this:
		last_row_result = SQLITE_DONE;
	}
	else {
		lastData->data = NULL;
		lastData->size = 0;
	}
	return lastData;
}

} } //end of namespace Freeworld:Impl
