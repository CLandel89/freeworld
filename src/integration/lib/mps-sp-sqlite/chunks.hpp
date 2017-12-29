#ifndef FREEWORLD_SQLITE_CHUNKS_HPP
#define FREEWORLD_SQLITE_CHUNKS_HPP

#include <sqlite3.h>

//#include <cstddef>

#include "src/integration-headers/mps-sp/chunks.hpp"
#include "src/integration-headers/mps-sp/integration.hpp"

namespace Freeworld { namespace Integration {

class ChunksPrivate {
public:
	IntegrationMpsSp* integration;
	sqlite3_stmt* open_read_stmt;
	BinData* lastData = nullptr;
	int last_row_result;

	ChunksPrivate(IntegrationMpsSp* integration);
	~ChunksPrivate();
	void delete_lastData();
	void prepare_chunks();
	void finalize_chunks();
};

} } //end of namespace Freeworld::Integration

#endif // FREEWORLD_SQLITE_CHUNKS_HPP
