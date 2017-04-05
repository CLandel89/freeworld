//TODO: don't use std::exit here!!
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

#include "src/integration/lib/mpc-sp-sdl/system.hpp"
//this source file implements the following interface headers:
#include "src/integration-headers/mpc-sp/input.hpp"

namespace Freeworld { namespace Integration {

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

bool poll_input(InputEvent* event) {
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
			return poll_input(event);
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
			return poll_input(event);
		return true;
	case SDL_KEYUP:
		if (ev.key.repeat!=0)
			return poll_input(event);
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
			return poll_input(event);
		return true;
	}
	return poll_input(event);
}

} } //end of namespace Freeworld:Integration
