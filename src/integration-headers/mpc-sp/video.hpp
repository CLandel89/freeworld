#ifndef VIDEO_H
#define VIDEO_H

namespace Freeworld { namespace Integration {

void frame_completed();
//set the resolution according to which graphics will be scaled:
void set_resolution(int32_t w, int32_t h);
void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b);

} } // end of namespace Freeworld::Integration

#endif //VIDEO_H
