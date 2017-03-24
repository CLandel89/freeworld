#include "src/integration/lib/mpc-sp-sdl/sdl.hpp"
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//SDL2_gfx
#include <SDL2/SDL2_rotozoom.h>

#include "src/mpc-sp/package_manager.hpp"
//helper functions and global variables:
#include "src/integration-headers/mpc-sp/wall.hpp"

namespace Freeworld { namespace Impl {

class WallPrivate {
public:
	SDL_Surface* img = NULL;

};

Wall::Wall(int32_t id) {
	priv = new WallPrivate();
	std::string fn = Freeworld::Common::get_package_manager()->fn_for_hash(id);
	if (fn.empty()) {
		priv->img = NULL;
		return;
	}
	SDL_Surface* tmp = IMG_Load(fn.c_str());
	if (tmp == NULL) {
		priv->img = NULL;
		return;
	}
	priv->img = zoomSurface(tmp, resolution_factor, resolution_factor, SMOOTHING_ON);
	SDL_FreeSurface(tmp);
}

Wall::~Wall() {
	if (priv->img != NULL) {
		SDL_FreeSurface(priv->img);
	}
	delete priv;
}

//#define DEBUG_ME

void Wall::draw(int32_t x, int32_t y, int32_t w, int32_t h, int32_t offset_x, int32_t offset_y) {
	SDL_Rect dstrect, srcrect;
	window_coordinates(x,y, &dstrect);
	int32_t screen_x=dstrect.x, screen_y=dstrect.y;
	int32_t screen_w = dstrect.w =  (int32_t)(w*resolution_factor);
	int32_t screen_h = dstrect.h =  (int32_t)(h*resolution_factor);
#ifndef DEBUG_ME //if in debugging/highlighting mode, always back up the wall
	if (priv->img == NULL) {
#endif
		SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
#ifndef DEBUG_ME
		return;
	}
#endif
	if (screen_w > priv->img->w)
		dstrect.w = srcrect.w = priv->img->w;
	else
		dstrect.w = srcrect.w = screen_w;
	if (screen_h > priv->img->h)
		dstrect.h = srcrect.h = priv->img->h;
	else
		dstrect.h = srcrect.h = screen_h;

	// translate offset to a valid range in the screen resolution
	offset_x = (int32_t)(offset_x*resolution_factor);
	offset_x %= priv->img->w;
	if (offset_x<0) offset_x+=priv->img->w;
	offset_y = (int32_t)(offset_y*resolution_factor);
	offset_y %= priv->img->h;
	if (offset_y<0) offset_y+=priv->img->h;

	// upper left corner
	srcrect.x = offset_x;
	srcrect.y = offset_y;
	SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
//	return;

	int32_t next_x = screen_x + priv->img->w - offset_x, next_y = screen_y;

	// upper part (excluding upper left and upper right corners)
	while (next_x < screen_x + screen_w - priv->img->w) {
		dstrect.x = next_x;
		srcrect.x = 0;
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
		next_x += priv->img->w;
	}

	// upper right corner
	dstrect.x = next_x;
	dstrect.y = screen_y;
	dstrect.w = srcrect.w = screen_x + screen_w - next_x;
	srcrect.x = 0;
	srcrect.y = offset_y;
	if (dstrect.w>0)
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);

	// left part (excluding upper left and lower left corners)
	srcrect.x = offset_x;
	srcrect.y = 0;
	next_y = screen_y + priv->img->h - offset_y;
	while (next_y < screen_y + screen_h - priv->img->h) {
		dstrect.x = screen_x;
		dstrect.y = next_y;
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
		next_y += priv->img->h;
	}

	// middle block
	srcrect.x = 0;
	srcrect.w = priv->img->w;
	srcrect.h = priv->img->h;
	next_x = screen_x + priv->img->w - offset_x;
    next_y = screen_y + priv->img->h - offset_y;
	while (next_x < screen_x + screen_w - priv->img->w) {
		next_y = screen_y + priv->img->h - offset_y;
		while (next_y < screen_y + screen_h - priv->img->h) {
			dstrect.x = next_x;
			dstrect.y = next_y;
			SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
			next_y += priv->img->h;
		}
		next_x += priv->img->w;
	}

	// right part (excluding upper right and lower right corners)
	srcrect.x = srcrect.y = 0;
	dstrect.w = srcrect.w = screen_x + screen_w - next_x;
	dstrect.h = srcrect.h = priv->img->h;
	next_y = screen_y + priv->img->h - offset_y;
	while (next_y < screen_y + screen_h - priv->img->h) {
		dstrect.x = next_x;
		dstrect.y = next_y;
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
		next_y += priv->img->h;
	}

	// lower left corner
	dstrect.x = next_x = screen_x;
	dstrect.y = next_y;
	srcrect.x = offset_x;
	srcrect.y = 0;
	srcrect.w = screen_x + screen_w - next_x;
	srcrect.h = screen_y + screen_h - next_y;
	if (srcrect.w>priv->img->w)
		srcrect.w = priv->img->w;
	dstrect.w = srcrect.w;
	dstrect.h = srcrect.h;
	if (dstrect.w>0 && dstrect.h>0)
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);

	// lower part (excluding lower left and lower right corners)
	srcrect.x = 0;
	dstrect.w = srcrect.w = priv->img->w;
	dstrect.h = srcrect.h = screen_y + screen_h - next_y;
	next_x = screen_x + priv->img->w - offset_x;
	while (next_x < screen_x + screen_w - priv->img->w) {
		dstrect.x = next_x;
		dstrect.y = next_y;
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);
		next_x += priv->img->w;
	}

	// lower right corner
	dstrect.w = srcrect.w = screen_x + screen_w - next_x;
	dstrect.h = srcrect.h = screen_y + screen_h - next_y;
	dstrect.x = next_x;
	dstrect.y = next_y;
	if (dstrect.w>0 && dstrect.h>0)
		SDL_BlitSurface(priv->img, &srcrect, window_surf, &dstrect);

#ifdef DEBUG_ME
	dstrect = {screen_x,screen_y, screen_w, 2};
	SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
	dstrect = {screen_x,screen_y, 2, screen_h};
	SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
	dstrect = {screen_x+screen_w-2,screen_y, 2, screen_h};
	SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
	dstrect = {screen_x,screen_y+screen_h-2, screen_w, 2};
	SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
#endif
}


} } //end of namespace Freeworld:Impl
