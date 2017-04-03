#ifndef WALL_H
#define WALL_H

namespace Freeworld { namespace Integration {

class WallPrivate;

class Wall {
	WallPrivate* priv;
public:
	Wall(int32_t id);
	~Wall();
	void draw (int32_t x, int32_t y, int32_t w, int32_t h, int32_t offset_x, int32_t offset_y);
};

} } // end of namespace Freeworld::Integration

#endif //WALL_H
