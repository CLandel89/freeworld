#ifndef CHUNKS_H
#define CHUNKS_H

namespace Freeworld { namespace Integration {

typedef struct {
	uint8_t* data;
	int32_t size;
} BinData;

void open_chunk(int32_t x, int32_t y, int32_t z);
//the implementing end has to free the BinData
//and its data component upon the next call
//and to close the db on the last, NULL returning call
BinData* read_chunk();

} } // end of namespace Freeworld::Integration

#endif //CHUNKS_H
