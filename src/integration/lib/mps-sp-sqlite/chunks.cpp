#include "src/integration/lib/mps-sp-sqlite/chunks.hpp"
#include "src/integration/lib/mps-sp-sqlite/integration.hpp"
#include "src/integration/lib/mps-sp-sqlite/util.hpp"
#include "src/integration-headers/mps-sp/integration.hpp"
// this source file implements the following header:
#include "src/integration-headers/mps-sp/chunks.hpp"

namespace Freeworld { namespace Integration {

// internal workings

ChunksPrivate::ChunksPrivate(IntegrationMpsSp* integration) {
	this->integration = integration;
}

ChunksPrivate::~ChunksPrivate() {
}

void ChunksPrivate::delete_lastData() {
	if (lastData==NULL) return;
	//this is done by SQLite:
	//if (lastData->size) delete lastData->data;
	delete lastData;
}

// module-wide data and functions

void ChunksPrivate::prepare_chunks() {
	auto rc = sqlite3_prepare_v2(integration->priv->sqlite3_db,
			"SELECT data FROM chunks WHERE x=? AND y=? AND z=?", -1,
			&open_read_stmt, NULL);
	ok_or_throw("PREPARE-chunks", rc, integration->priv->sqlite3_db);
}

void ChunksPrivate::finalize_chunks() {
	auto rc = sqlite3_finalize(open_read_stmt);
	ok_or_throw("FINALIZE-chunks", rc, integration->priv->sqlite3_db);
	delete_lastData();
}

// integration

Chunks::Chunks(IntegrationMpsSp* integration) {
	this->integration = integration;
	priv = new ChunksPrivate(integration);
}
Chunks::~Chunks() {
	delete priv;
}

void Chunks::open(int32_t x, int32_t y, int32_t z) {
//	std::cout << x + ", " + y + ", " + z;
	auto rc = sqlite3_reset(priv->open_read_stmt);
	ok_or_throw("RESET-chunks", rc, integration->priv->sqlite3_db);
	rc = sqlite3_bind_int(priv->open_read_stmt, 1, x);
	ok_or_throw("BIND-chunks", rc, integration->priv->sqlite3_db);
	rc = sqlite3_bind_int(priv->open_read_stmt, 2, y);
	ok_or_throw("BIND-chunks", rc, integration->priv->sqlite3_db);
	rc = sqlite3_bind_int(priv->open_read_stmt, 3, z);
	ok_or_throw("BIND-chunks", rc, integration->priv->sqlite3_db);
	rc = sqlite3_step(priv->open_read_stmt);
	if (rc!=SQLITE_ROW && rc!=SQLITE_DONE)
		ok_or_throw("STEP-chunks", rc, integration->priv->sqlite3_db);
	priv->last_row_result = rc;
}

BinData* Chunks::read() {
	priv->delete_lastData();
	priv->lastData = new BinData;
	if (priv->last_row_result == SQLITE_ROW) {
		priv->lastData->data = (uint8_t*)sqlite3_column_blob(priv->open_read_stmt, 0);
		priv->lastData->size = (int32_t)sqlite3_column_bytes(priv->open_read_stmt, 0);
		//as longs as no incremental blob stuff is implemented here, we
		//can complete a chunk like this:
		priv->last_row_result = SQLITE_DONE;
	}
	else {
		priv->lastData->data = NULL;
		priv->lastData->size = 0;
	}
	return priv->lastData;
}

} } //end of namespace Freeworld:Integration
