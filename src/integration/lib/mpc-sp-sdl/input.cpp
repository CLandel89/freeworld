#include "src/integration/lib/mpc-sp-sdl/input.hpp"
#include "src/integration/lib/mpc-sp-sdl/integration.hpp"
#include "src/mpc-mps-sp/utils.hpp"
//this source file implements the following interface header:
#include "src/integration-headers/mpc-sp/input.hpp"

//TODO: don't use std::exit here!!
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

namespace Freeworld { namespace Integration {

// internal definitions

CiButton ciButton (SDL_MouseButtonEvent& mbev) {
	switch (mbev.button) {
	case 1:
		return CiButton::MOUSEL;
	case 2:
		return CiButton::MOUSEM;
	case 3:
		return CiButton::MOUSER;
	}
	//unknown sdl button => left mouse button
	return CiButton::MOUSEL;
}

CiButton ciButton (SDL_MouseWheelEvent& mwev) {
	if (mwev.y>0)
		return CiButton::MOUSEU;
	else if (mwev.y<0)
		return CiButton::MOUSED;
	return (CiButton)0;
}

// exported definitions

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
		CiButton button;
		float x, y;
		auto& ip = integration->priv;
		auto& instance = integration->instance;
		uint32_t lw = ip->letterbox_w;
		uint32_t lh = ip->letterbox_h;
		uint32_t ww = ip->window_w - 2*lw;
		uint32_t wh = ip->window_h - 2*lh;
		switch (ev.type) {
		case SDL_QUIT:
			instance->finish();
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
			button = priv->keymap[ev.key.keysym.scancode];
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
		break;
		case SDL_MOUSEMOTION:
			if (ev.motion.x < lw || ev.motion.y < lh
					|| ev.motion.x > lw+ww || ev.motion.y > lh+wh)
				return poll(event);
			// encoding: 2 uint16 (0..0xffff)
			x = ((float)(ev.motion.x-lw)) / ((float)ww);
			y = ((float)(ev.motion.y-lh)) / ((float)wh);
			event->type = CiType::MOUSE;
			event->value.raw = ((uint32_t)(x*0xffff)) | (((uint32_t)(y*0xffff))<<16);
			return true;
		break;
		case SDL_MOUSEWHEEL:
			button = ciButton(ev.wheel);
			if (button == 0)
				continue;
			event->type = CiType::PRESS;
			event->value.button = button;
			return true;
		break;
		case SDL_MOUSEBUTTONDOWN:
			event->type = CiType::PRESS;
			button = ciButton(ev.button);
			if (button == 0)
				continue;
			return true;
		break;
		case SDL_MOUSEBUTTONUP:
			event->type = CiType::RELEASE;
			button = ciButton(ev.button);
			if (button == 0)
				continue;
			return true;
		break;
		}
	}
	//queue empty
	memset(event, 0, sizeof(*event));
	return false;
}

} } //end of namespace Freeworld:Integration
