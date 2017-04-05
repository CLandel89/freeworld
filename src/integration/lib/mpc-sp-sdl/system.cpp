#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>

//this source file implements the following interface header:
#include "src/integration-headers/mpc-mps-sp/system.hpp"

namespace Freeworld { namespace Integration {

// externable variables for internal use in this lib

SDL_Window* window;
SDL_Surface* window_surf;
SDL_PixelFormat* window_px_form;
int window_w = 1024;
int window_h = 768;
int letterbox_w = 0;
int letterbox_h = 0;
float resolution_factor = 1.0f;

// helper functions

void window_coordinates (int32_t x, int32_t y, SDL_Rect* dstrect) {
	dstrect->x = (int32_t) (x*resolution_factor) + letterbox_w;
	dstrect->y = (int32_t) (y*resolution_factor) + letterbox_h;
}

int32_t encode_f (float f) {
	return (int32_t) (f*65536);
}

// integration

void start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Freeworld", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_OPENGL);
	window_surf = SDL_GetWindowSurface(window);
	window_px_form = window_surf->format;
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void stop() {
	IMG_Quit();
	SDL_Quit();
}

} } //end of namespace Freeworld:Integration
