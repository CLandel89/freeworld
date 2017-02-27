#ifndef HANDLE_MI_H
#define HANDLE_MI_H

#include <map>

#include "package_manager.h"

#include "../impl-headers/mpc-sp/sprite.h"
#include "../impl-headers/mpc-sp/wall.h"
#include "../impl-headers/mpc-sp/video.h"

namespace Freeworld { namespace Common {

using Freeworld::Impl::Sprite;
using Freeworld::Impl::Wall;

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

} } //end of namespace Freeworld::Common

#endif //HANDLE_MI_H
