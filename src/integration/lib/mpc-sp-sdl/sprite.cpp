#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//SDL2_gfx
#include <SDL2/SDL2_rotozoom.h>

#include "src/mpc-sp/package_manager.hpp"

#include "src/integration/lib/mpc-sp-sdl/system.hpp"
//this source file implements the following interface headers:
#include "src/integration-headers/mpc-sp/sprite.hpp"

namespace Freeworld { namespace Integration {

class SpritePrivate {
public:
	SDL_Surface* img = NULL;
};

Sprite::Sprite(int32_t id) {
	priv = new SpritePrivate();
	std::string fn = Freeworld::get_package_manager()->fn_for_hash(id);
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

Sprite::~Sprite() {
	if (priv->img != NULL) {
		SDL_FreeSurface(priv->img);
	}
	delete priv;
}

void Sprite::draw(int32_t x, int32_t y) {
	SDL_Rect dstrect;
	window_coordinates(x,y, &dstrect);
	if (priv->img == NULL) {
		dstrect.w = (window_w - letterbox_w*2) / 5;
		dstrect.h = dstrect.w;
		SDL_FillRect(window_surf, &dstrect, SDL_MapRGB(window_px_form, 255, 0, 0));
		return;
	}
	SDL_BlitSurface(priv->img, NULL, window_surf, &dstrect);
}

} } //end of namespace Freeworld:Integration
