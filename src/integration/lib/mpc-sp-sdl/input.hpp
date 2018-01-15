#ifndef FREEWORLD_SDL_INPUT_HPP
#define FREEWORLD_SDL_INPUT_HPP

#include <SDL2/SDL_scancode.h>

namespace Freeworld { namespace Integration {

class InputPrivate {
public:
	float x_tmp = 0, y_tmp = 0;
	SDL_Scancode jump = SDL_SCANCODE_SPACE,
	     walljump = SDL_SCANCODE_LALT,
	     up = SDL_SCANCODE_UP,
	     down = SDL_SCANCODE_DOWN,
	     left = SDL_SCANCODE_LEFT,
	     right = SDL_SCANCODE_RIGHT,
	     a = SDL_SCANCODE_A,
	     b = SDL_SCANCODE_S,
	     c = SDL_SCANCODE_Z,
	     d = SDL_SCANCODE_X,
	     escape = SDL_SCANCODE_ESCAPE;
};

} } // end of namespace Freeworld::Integration

#endif // FREEWORLD_SDL_INPUT_HPP
