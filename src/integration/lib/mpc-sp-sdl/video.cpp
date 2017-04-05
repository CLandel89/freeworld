#include <SDL2/SDL.h>

#include "src/integration/lib/mpc-sp-sdl/system.hpp"
//this source file implements the following interface headers:
#include "src/integration-headers/mpc-sp/video.hpp"

namespace Freeworld { namespace Integration {

// V I D E O

void frame_completed() {
	//draw letterbox (cover regions from the frame that are not to be shown)
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	auto black = SDL_MapRGB(window_px_form, 0,0,0);
	if (letterbox_w) {
		dstrect.w = letterbox_w;
		dstrect.h = window_h;
		SDL_FillRect(window_surf, &dstrect, black);
		dstrect.x = window_w - letterbox_w;
		SDL_FillRect(window_surf, &dstrect, black);
	}
	else {
		dstrect.w = window_w;
		dstrect.h = letterbox_h;
		SDL_FillRect(window_surf, &dstrect, black);
		dstrect.y = window_h - letterbox_h;
		SDL_FillRect(window_surf, &dstrect, black);
	}
	SDL_UpdateWindowSurface(window);
}

int32_t resolution_w = window_w;
int32_t resolution_h = window_h;
void set_resolution(int32_t w, int32_t h) {
	resolution_w = w;
	resolution_h = h;
	//physical aspect ratio
	float window_w_h = (float)window_w / (float)window_h;
	//virtual aspect ratio
	float resolution_w_h = (float)resolution_w / (float)resolution_h;
	if(window_w_h > resolution_w_h) {
		letterbox_h = 0;
		resolution_factor = (float)window_h / (float)resolution_h;
		letterbox_w = (int)
				(window_w - ((float) resolution_w * resolution_factor)) / 2;
	}
	else {
		letterbox_w = 0;
		resolution_factor = (float)window_w / (float)resolution_w;
		letterbox_h = (int)
				(window_h - ((float) resolution_h * resolution_factor)) / 2;
	}
}

void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b) {
	SDL_Rect dstrect;
	window_coordinates(x,y, &dstrect);
	dstrect.w = (int32_t) (w*resolution_factor);
	dstrect.h = (int32_t) (h*resolution_factor);
	SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, r, g, b));
}

} } //end of namespace Freeworld:Integration
