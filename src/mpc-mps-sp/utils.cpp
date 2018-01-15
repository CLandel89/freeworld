#include "src/mpc-mps-sp/utils.hpp"

namespace Freeworld {

int32_t string_hash (std::string str) {
	int32_t result = 0;
	for (char& c : str) {
		result *= 31;
		result += c;
	}
	return result;
}

int32_t encode_f(float f) {
	return (int32_t) (f*65536);
}


void write_le(int32_t value, uint8_t* buf) {
	buf[0] = (uint8_t) value;
	buf[1] = (uint8_t) (value>>8);
	buf[2] = (uint8_t) (value>>16);
	buf[3] = (uint8_t) (value>>24);
}

void write_le(uint32_t value, uint8_t* buf) {
	write_le((int32_t)value, buf);
}

} // end of namespace Freeworld
