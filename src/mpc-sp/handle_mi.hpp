#ifndef HANDLE_MI_HPP
#define HANDLE_MI_HPP

#include <map>

#include "src/integration-headers/mpc-sp/integration.hpp"
#include "src/integration-headers/mpc-sp/sprite.hpp"
#include "src/integration-headers/mpc-sp/wall.hpp"

namespace Freeworld {

class HandleMi
{
	enum class Mi {
#include "dist/enums/mi.enum"
	};

	Freeworld::Integration::IntegrationMpcSp* integration;

	std::map<int32_t, Freeworld::Integration::Sprite*> sprites;
	std::map<int32_t, Freeworld::Integration::Wall*> walls;

	uint8_t* current_data = NULL;
	int current_data_length = 0;
	int current_data_read = 0;
	int current_data_read_reset = 0;
	void* raw;

	void* read (int length);
	//when a MI is only partially transmitted,
	//the pointer is reset to the beginning of it
	void read_reset();
	void read_reset_set();

public:
	HandleMi(Freeworld::Integration::IntegrationMpcSp* integration);
	~HandleMi();
	void handle_mi (int length, uint8_t* data);
};

} //end of namespace Freeworld

#endif // HANDLE_MI_HPP
