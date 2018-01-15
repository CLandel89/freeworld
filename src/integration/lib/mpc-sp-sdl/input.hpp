#ifndef FREEWORLD_SDL_INPUT_HPP
#define FREEWORLD_SDL_INPUT_HPP

#include <SDL2/SDL_scancode.h>
#include <map>

#include "src/integration-headers/mpc-sp/input.hpp"

namespace Freeworld { namespace Integration {

class InputPrivate {
public:
	//the keymap for CiType::PRESS and CiType::RELEASE type events
	std::map<SDL_Scancode, CiButton>
		keymap = {
			{SDL_SCANCODE_SPACE, CiButton::JUMP},
			{SDL_SCANCODE_LALT, CiButton::WALLJUMP},
			{SDL_SCANCODE_A, CiButton::A},
			{SDL_SCANCODE_S, CiButton::B},
			{SDL_SCANCODE_Z, CiButton::C},
			{SDL_SCANCODE_X, CiButton::D},
			{SDL_SCANCODE_ESCAPE, CiButton::ESCAPE},
	};
	//these represent the last state on the axes,
	//so releasing an arrow in one direction won't
	//cancel out an arrow in the other direction
	float x_tmp = 0, y_tmp = 0;
	//a keymap for 2 axes
	SDL_Scancode up = SDL_SCANCODE_UP,
	             down = SDL_SCANCODE_DOWN,
	             left = SDL_SCANCODE_LEFT,
	             right = SDL_SCANCODE_RIGHT;
};

} } // end of namespace Freeworld::Integration

#endif // FREEWORLD_SDL_INPUT_HPP
