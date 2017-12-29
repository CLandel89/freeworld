namespace Freeworld { namespace Integration {
class Wall;
} }

#ifndef FREEWORLD_INTEGRATION_WALL_HPP
#define FREEWORLD_INTEGRATION_WALL_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"

namespace Freeworld { namespace Integration {

class WallPrivate;

class Wall {
	WallPrivate* priv;
public:
	Wall(int32_t id, IntegrationMpcSp* integration);
	~Wall();
	void draw (int32_t x, int32_t y, int32_t w, int32_t h, int32_t offset_x, int32_t offset_y, IntegrationMpcSp* integration);
};

} } // end of namespace Freeworld::Integration

#endif // FREEWORLD_INTEGRATION_WALL_HPP
