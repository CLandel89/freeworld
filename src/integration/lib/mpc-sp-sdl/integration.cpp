#include "src/integration/lib/mpc-sp-sdl/integration.hpp"
#include "src/integration-headers/mpc-sp/input.hpp"
#include "src/integration-headers/mpc-sp/video.hpp"
#include "src/mpc-sp/instance.hpp"
//this source file implements the following interface header:
#include "src/integration-headers/mpc-sp/integration.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Freeworld { namespace Integration {

// internal definitions:

int instances = 0;

void IntegrationMpcSpPrivate::window_coordinates(int32_t x, int32_t y, SDL_Rect* dstrect) {
	dstrect->x = (int32_t) (x*resolution_factor) + letterbox_w;
	dstrect->y = (int32_t) (y*resolution_factor) + letterbox_h;
}

// implementation (exported definitions):

IntegrationMpcSp::IntegrationMpcSp(InstanceMpcSp* instance) {
	this->instance = instance;
	priv = new IntegrationMpcSpPrivate();
	input = new Input(this);
	video = new Video(this);
}

IntegrationMpcSp::~IntegrationMpcSp() {
	delete priv;
}

void IntegrationMpcSp::init() {
	if (instances == 0) {
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	}
	priv->window = SDL_CreateWindow(
			"Freeworld",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			priv->window_w, priv->window_h,
			SDL_WINDOW_OPENGL);
	priv->window_surf = SDL_GetWindowSurface(priv->window);
	priv->window_px_form = priv->window_surf->format;
	instances++;
}

void IntegrationMpcSp::quit() {
	instances--;
	if (instances == 0) {
		IMG_Quit();
		SDL_Quit();
	}
}

} } //end of namespace Freeworld:Integration
