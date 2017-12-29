#ifndef FREEWORLD_SDL_INTEGRATION_HPP
#define FREEWORLD_SDL_INTEGRATION_HPP

#include <SDL2/SDL.h>

namespace Freeworld { namespace Integration {

// Called "private", this class is used in the whole SDL module.
class IntegrationMpcSpPrivate {
public:
	SDL_Window* window;
	SDL_Surface* window_surf;
	SDL_PixelFormat* window_px_form;
	int window_w = 1024;
	int window_h = 768;
	int letterbox_w = 0;
	int letterbox_h = 0;
	float resolution_factor = 1.0f;
	void window_coordinates (int32_t x, int32_t y, SDL_Rect* dstrect);
	int32_t encode_f (float f);
};

} } // end of namespace Freeworld:Integration

#endif // FREEWORLD_SDL_INTEGRATION_HPP
