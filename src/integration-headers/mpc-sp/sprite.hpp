namespace Freeworld { namespace Integration {
class Sprite;
} }

#ifndef FREEWORLD_INTEGRATION_SPRITE_HPP
#define FREEWORLD_INTEGRATION_SPRITE_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"

namespace Freeworld { namespace Integration {

class SpritePrivate;

class Sprite {
public:
	SpritePrivate* priv;
	Sprite(int32_t id, IntegrationMpcSp* integration);
	~Sprite();
	void draw (int32_t x, int32_t y, IntegrationMpcSp* integration);
};

} } //end of namespace Freeworld::Integration

#endif //FREEWORLD_INTEGRATION_SPRITE_HPP
