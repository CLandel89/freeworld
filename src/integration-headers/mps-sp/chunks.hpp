namespace Freeworld { namespace Integration {
class Chunks;
} }

#ifndef FREEWORLD_INTEGRATION_CHUNKS_HPP
#define FREEWORLD_INTEGRATION_CHUNKS_HPP

#include "src/integration-headers/mps-sp/integration.hpp"

#include <stdint.h>

namespace Freeworld { namespace Integration {

typedef struct {
	uint8_t* data;
	int32_t size;
} BinData;

class ChunksPrivate;
class Chunks {
public:
	ChunksPrivate* priv;
	IntegrationMpsSp* integration;

	Chunks(IntegrationMpsSp* integration);
	~Chunks();
	void open(int32_t x, int32_t y, int32_t z);
	//the implementing end has to free the BinData
	//and its data component upon the next call
	//and to close the db on the last, NULL returning call
	BinData* read();
};

} } // end of namespace Freeworld::Integration

#endif // FREEWORLD_INTEGRATION_CHUNKS_HPP
