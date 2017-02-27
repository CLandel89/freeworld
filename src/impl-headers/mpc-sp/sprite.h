#ifndef SPRITE_H
#define SPRITE_H

namespace Freeworld { namespace Impl {

class SpritePrivate;

class Sprite {
	SpritePrivate* priv;
public:
	Sprite(int32_t id);
	~Sprite();
	void draw (int32_t x, int32_t y);
};

} } //end of namespace Freeworld::Impl

#endif //SPRITE_H
