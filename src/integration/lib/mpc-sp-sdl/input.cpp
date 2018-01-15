#include "src/integration/lib/mpc-sp-sdl/input.hpp"
#include "src/mpc-mps-sp/utils.hpp"
//this source file implements the following interface header:
#include "src/integration-headers/mpc-sp/input.hpp"

//TODO: don't use std::exit here!!
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

namespace Freeworld { namespace Integration {

Input::Input(IntegrationMpcSp* integration) {
	this->integration = integration;
	priv = new InputPrivate();
}

Input::~Input() {
	delete priv;
}

bool Input::poll(InputEvent* event) {
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
			return poll(event);
		event->type = CiType::PRESS;
		if (ev.key.keysym.scancode == priv->jump)
			event->value = CiButton::JUMP;
		else if (ev.key.keysym.scancode == priv->walljump)
			event->value = CiButton::WALLJUMP;
		else if (ev.key.keysym.scancode == priv->up) {
			event->type = CiType::AXIS_Y;
			event->value = encode_f(-1);
			priv->y_tmp = -1;
		}
		else if (ev.key.keysym.scancode == priv->down) {
			event->type = CiType::AXIS_Y;
			event->value = encode_f(1);
			priv->y_tmp = 1;
		}
		else if (ev.key.keysym.scancode == priv->left) {
			event->type = CiType::AXIS_X;
			event->value = encode_f(-1);
			priv->x_tmp = -1;
		}
		else if (ev.key.keysym.scancode == priv->right) {
			event->type = CiType::AXIS_X;
			event->value = encode_f(1);
			priv->x_tmp = 1;
		}
		else if (ev.key.keysym.scancode == priv->a)
			event->value = CiButton::A;
		else if (ev.key.keysym.scancode == priv->b)
			event->value = CiButton::B;
		else if (ev.key.keysym.scancode == priv->c)
			event->value = CiButton::C;
		else if (ev.key.keysym.scancode == priv->d)
			event->value = CiButton::D;
		else if (ev.key.keysym.scancode == priv->escape)
			event->value = CiButton::ESCAPE;
		else
			//this SDL event is not from a defined key
			//so we need to process the next SDL event
			return poll(event);
		return true;
	case SDL_KEYUP:
		if (ev.key.repeat!=0)
			return poll(event);
		event->type = CiType::RELEASE;
		if (ev.key.keysym.scancode == priv->jump)
			event->value = CiButton::JUMP;
		else if (ev.key.keysym.scancode == priv->walljump)
			event->value = CiButton::WALLJUMP;
		else if (ev.key.keysym.scancode == priv->up) {
			if (priv->y_tmp != -1)
				return poll(event);
			event->type = CiType::AXIS_Y;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.scancode == priv->down) {
			if (priv->y_tmp != 1)
				return poll(event);
			event->type = CiType::AXIS_Y;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.scancode == priv->left) {
			if (priv->x_tmp != -1)
				return poll(event);
			event->type = CiType::AXIS_X;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.scancode == priv->right) {
			if (priv->x_tmp != 1)
				return poll(event);
			event->type = CiType::AXIS_X;
			event->value = encode_f(0);
		}
		else if (ev.key.keysym.scancode == priv->a)
			event->value = CiButton::A;
		else if (ev.key.keysym.scancode == priv->b)
			event->value = CiButton::B;
		else if (ev.key.keysym.scancode == priv->c)
			event->value = CiButton::C;
		else if (ev.key.keysym.scancode == priv->d)
			event->value = CiButton::D;
		else if (ev.key.keysym.scancode == priv->escape)
			event->value = CiButton::ESCAPE;
		else
			return poll(event);
		return true;
	}
	return poll(event);
}

} } //end of namespace Freeworld:Integration
