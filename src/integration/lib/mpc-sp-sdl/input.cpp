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
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			//TODO: find a sane way to implement this
			std::cout << "Received SDL_QUIT. Shutting down, but not softly (implement me!).\n";
			std::exit(0);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (ev.key.repeat!=0)
				continue;
			float axis_dir;
			if (ev.type==SDL_KEYDOWN) {
				event->type = CiType::PRESS;
				axis_dir = 1;
			}
			else {
				event->type = CiType::RELEASE;
				axis_dir = 0;
			}
			CiButton button = priv->keymap[ev.key.keysym.scancode];
			if (button != 0) {
				event->value.button = button;
				return true;
			}
			if (ev.key.keysym.scancode == priv->up) {
				if (axis_dir==0 && priv->y_tmp>0)
				  //don't cancel out a "down" press
				  continue;
				event->type = CiType::AXIS_Y;
				event->value.raw = encode_f(-axis_dir);
				priv->y_tmp = -1;
				return true;
			}
			else if (ev.key.keysym.scancode == priv->down) {
				if (axis_dir==0 && priv->y_tmp<0)
				  //don't cancel out an "up" press
				  continue;
				event->type = CiType::AXIS_Y;
				event->value.raw = encode_f(axis_dir);
				priv->y_tmp = 1;
				return true;
			}
			else if (ev.key.keysym.scancode == priv->left) {
				if (axis_dir==0 && priv->x_tmp>0)
				  //don't cancel out a "right" press
				  continue;
				event->type = CiType::AXIS_X;
				event->value.raw = encode_f(-axis_dir);
				priv->x_tmp = -1;
				return true;
			}
			else if (ev.key.keysym.scancode == priv->right) {
				if (axis_dir==0 && priv->x_tmp<0)
				  //don't cancel out a "left" press
				  continue;
				event->type = CiType::AXIS_X;
				event->value.raw = encode_f(axis_dir);
				priv->x_tmp = 1;
				return true;
			}
		}
	}
	//queue empty
	memset(event, 0, sizeof(*event));
	return false;
}

} } //end of namespace Freeworld:Integration
