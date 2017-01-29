#include <map>

#include "package_manager.h"
#include "../impl-headers/sprite.h"
#include "../impl-headers/wall.h"

#ifndef HANDLE_MI_H
#define HANDLE_MI_H

namespace Jumpfree { namespace Common {

using Jumpfree::Impl::Sprite;
using Jumpfree::Impl::Wall;

class MiParser
{
	enum class Mi {
#include "../../dist/enums/mi.enum"
	};

	std::map<int32_t, Sprite*> sprites;
	std::map<int32_t, Wall*> walls;

	uint8_t* current_data = NULL;
	int current_data_length = 0;
	int current_data_read = 0;
	int current_data_read_reset = 0;

	void* read (int length);
	//when a single MI is only partially transmitted,
	//the pointer is reset to the beginning of it
	void read_reset();
	void read_reset_set();

public:

	MiParser();
	~MiParser();
	void parse_mi (int length, uint8_t* data);
};

} } //end of namespace Jumpfree::Common

#endif //HANDLE_MI_H
