#ifndef SPRITE_H
#define SPRITE_H

namespace Jumpfree { namespace Impl {

class SpritePrivate;

class Sprite {
	SpritePrivate* priv;
public:
	Sprite(int32_t id);
	~Sprite();
	void draw (int32_t x, int32_t y);
};

} } //end of namespace Jumpfree::Impl

#endif //SPRITE_H
