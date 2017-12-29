#include "src/integration/lib/mpc-sp-sdl/video.hpp"
#include "src/integration/lib/mpc-sp-sdl/integration.hpp" // "private" area of Integration
//this source file implements the following interface header:
#include "src/integration-headers/mpc-sp/video.hpp"
#include <SDL2/SDL.h>

namespace Freeworld { namespace Integration {

Video::Video(IntegrationMpcSp* integration) {
	this->integration = integration;
	priv = new VideoPrivate;
}
Video::~Video() {
	delete priv;
}

void Video::frame_completed() {
	auto& ip = * integration->priv;
	//draw letterbox (cover regions from the frame that are not to be shown)
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	auto black = SDL_MapRGB(ip.window_px_form, 0,0,0);
	if (ip.letterbox_w) {
		dstrect.w = ip.letterbox_w;
		dstrect.h = ip.window_h;
		SDL_FillRect(ip.window_surf, &dstrect, black);
		dstrect.x = ip.window_w - ip.letterbox_w;
		SDL_FillRect(ip.window_surf, &dstrect, black);
	}
	else {
		dstrect.w = ip.window_w;
		dstrect.h = ip.letterbox_h;
		SDL_FillRect(ip.window_surf, &dstrect, black);
		dstrect.y = ip.window_h - ip.letterbox_h;
		SDL_FillRect(ip.window_surf, &dstrect, black);
	}
	SDL_UpdateWindowSurface(ip.window);
}

void Video::set_resolution(int32_t w, int32_t h) {
	auto& ip = * integration->priv;
	priv->resolution_w = w;
	priv->resolution_h = h;
	//physical aspect ratio
	float window_w_h = (float)ip.window_w / (float)ip.window_h;
	//virtual aspect ratio
	float resolution_w_h = (float)priv->resolution_w / (float)priv->resolution_h;
	if(window_w_h > resolution_w_h) {
		ip.letterbox_h = 0;
		ip.resolution_factor = (float)ip.window_h / (float)priv->resolution_h;
		ip.letterbox_w = (int)
				(ip.window_w - ((float) priv->resolution_w * ip.resolution_factor)) / 2;
	}
	else {
		ip.letterbox_w = 0;
		ip.resolution_factor = (float)ip.window_w / (float)priv->resolution_w;
		ip.letterbox_h = (int)
				(ip.window_h - ((float) priv->resolution_h * ip.resolution_factor)) / 2;
	}
}

void Video::fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b) {
	auto& ip = * integration->priv;
	SDL_Rect dstrect;
	ip.window_coordinates(x,y, &dstrect);
	dstrect.w = (int32_t) (w*ip.resolution_factor);
	dstrect.h = (int32_t) (h*ip.resolution_factor);
	SDL_FillRect(ip.window_surf, &dstrect, SDL_MapRGB(ip.window_px_form, r, g, b));
}

} } //end of namespace Freeworld:Integration
