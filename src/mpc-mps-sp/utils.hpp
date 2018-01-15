#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdint.h>
#include <string>

namespace Freeworld {

int32_t string_hash (std::string str);
int32_t encode_f (float f);
/** Writes a 32-bit value in Little Endian format into the specified buffer. */
void write_le(int32_t value, uint8_t* buf);
/** @see write_le(int32,uint8_t*) */
void write_le(uint32_t value, uint8_t* buf);

} // end of namespace Freeworld

#endif // UTILS_HPP
