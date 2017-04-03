#ifndef SPRITE_H
#define SPRITE_H

namespace Freeworld { namespace Integration {

class SpritePrivate;

class Sprite {
	SpritePrivate* priv;
public:
	Sprite(int32_t id);
	~Sprite();
	void draw (int32_t x, int32_t y);
};

} } //end of namespace Freeworld::Integration

#endif //SPRITE_H
