#include <string>
//TODO: don't use std::exit here!!
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>
//SDL2_gfx
#include <SDL2/SDL2_rotozoom.h>

#include "../../../common-mpc-sp/package_manager.h"

//this source file implements the following interface headers:
#include "../../../impl-headers/mpc-sp/control.h"
#include "../../../impl-headers/mpc-sp/general.h"
#include "../../../impl-headers/mpc-sp/sprite.h"
#include "../../../impl-headers/mpc-sp/video.h"

namespace Freeworld { namespace Impl {

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

// G E N E R A L

void init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Freeworld", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_OPENGL);
	window_surf = SDL_GetWindowSurface(window);
	window_px_form = window_surf->format;
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void quit() {
	IMG_Quit();
	SDL_Quit();
}

// C O N T R O L

SDL_Keycode jump = SDLK_SPACE;
SDL_Keycode walljump = SDLK_LALT;
SDL_Keycode up = SDLK_UP;
SDL_Keycode down = SDLK_DOWN;
SDL_Keycode left = SDLK_LEFT;
SDL_Keycode right = SDLK_RIGHT;
SDL_Keycode a = SDLK_a;
SDL_Keycode b = SDLK_s;
SDL_Keycode c = SDLK_z;
SDL_Keycode d = SDLK_x;

float x_tmp = 0, y_tmp = 0;

bool poll_event(InputEvent* event) {
	SDL_Event ev;
	if (! SDL_PollEvent(&ev))
		return false;
	switch (ev.type) {
	case SDL_QUIT:
		//TODO: find a sane way to implement this
		std::cout << "Received SDL_QUIT. Shutting down, but not softly (implement me!).\n";
		std::exit(0);
		break;
	case SDL_KEYDOWN:
		if (ev.key.repeat!=0)
			return poll_event(event);
		event->type = CiType::PRESS;
		if (ev.key.keysym.sym == jump)
			event->value = CiButton::JUMP;
		else if (ev.key.keysym.sym == walljump)
			event->value = CiButton::WALLJUMP;
		else if (ev.key.keysym.sym == up) {
			event->type = CiType::AXIS_Y;
			event->value = encode_f(-1);
			y_tmp = -1;
		}
		else if (ev.key.keysym.sym == down) {
			event->type = CiType::AXIS_Y;
			event->value = encode_f(1);
			y_tmp = 1;
		}
		else if (ev.key.keysym.sym == left) {
			event->type = CiType::AXIS_X;
			event->value = encode_f(-1);
			x_tmp = -1;
		}
		else if (ev.key.keysym.sym == right) {
			event->type = CiType::AXIS_X;
			event->value = encode_f(1);
			x_tmp = 1;
		}
		else if (ev.key.keysym.sym == a)
			event->value = CiButton::A;
		else if (ev.key.keysym.sym == b)
			event->value = CiButton::B;
		else if (ev.key.keysym.sym == c)
			event->value = CiButton::C;
		else if (ev.key.keysym.sym == d)
			event->value = CiButton::D;
		else
			return poll_event(event);
		return true;
	case SDL_KEYUP:
		if (ev.key.repeat!=0)
			return poll_event(event);
		event->type = CiType::RELEASE;
		if (ev.key.keysym.sym == jump)
			event->value = CiButton::JUMP;
		else if (ev.key.keysym.sym == walljump)
			event->value = CiButton::WALLJUMP;
		else if (ev.key.keysym.sym == up) {
			if (y_tmp != -1)
				return false;
			event->type = CiType::AXIS_Y;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.sym == down) {
			if (y_tmp != 1)
				return false;
			event->type = CiType::AXIS_Y;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.sym == left) {
			if (x_tmp != -1)
				return false;
			event->type = CiType::AXIS_X;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.sym == right) {
			if (x_tmp != 1)
				return false;
			event->type = CiType::AXIS_X;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.sym == a)
			event->value = CiButton::A;
		else if (ev.key.keysym.sym == b)
			event->value = CiButton::B;
		else if (ev.key.keysym.sym == c)
			event->value = CiButton::C;
		else if (ev.key.keysym.sym == d)
			event->value = CiButton::D;
		else
			return poll_event(event);
		return true;
	}
	return poll_event(event);
}

// S P R I T E

class SpritePrivate {
public:
	SDL_Surface* img = NULL;
};
Sprite::Sprite(int32_t id) {
	priv = new SpritePrivate();
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

} } //end of namespace Freeworld:Impl
