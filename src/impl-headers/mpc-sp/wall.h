#ifndef WALL_H
#define WALL_H

namespace Freeworld { namespace Impl {

class WallPrivate;

class Wall {
	WallPrivate* priv;
public:
	Wall(int32_t id);
	~Wall();
	void draw (int32_t x, int32_t y, int32_t w, int32_t h, int32_t offset_x, int32_t offset_y);
};

} } //end of namespace Freeworld::Impl

#endif //WALL_H
