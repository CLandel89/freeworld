#include "utils.h"

namespace Freeworld { namespace Common {

int32_t string_hash (std::string str) {
	int32_t result = 0;
	for (char& c : str) {
		result *= 31;
		result += c;
	}
	return result;
}

} } // end of namespace Freeworld::Common
