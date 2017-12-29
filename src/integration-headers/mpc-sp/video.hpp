namespace Freeworld { namespace Integration {
class Video;
} }

#ifndef FREEWORLD_INTEGRATION_VIDEO_HPP
#define FREEWORLD_INTEGRATION_VIDEO_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"

#include <stdint.h>

namespace Freeworld { namespace Integration {

class VideoPrivate;

class Video {
public:
	VideoPrivate* priv;
	IntegrationMpcSp* integration;
	Video(IntegrationMpcSp* integration);
	~Video();
	void frame_completed();
	//set the resolution according to which graphics will fit in the drawing area:
	void set_resolution(int32_t w, int32_t h);
	void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b);
};

} } // end of namespace Freeworld::Integration

#endif // FREEWORLD_INTEGRATION_VIDEO_HPP
