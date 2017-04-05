#ifndef FREEWORLD_SDL_SYSTEM_HPP
#define FREEWORLD_SDL_SYSTEM_HPP

#include <SDL2/SDL.h>

namespace Freeworld { namespace Integration {

extern SDL_Window* window;
extern SDL_Surface* window_surf;
extern SDL_PixelFormat* window_px_form;
extern int window_w;
extern int window_h;
extern int letterbox_w;
extern int letterbox_h;
extern float resolution_factor;
void window_coordinates (int32_t x, int32_t y, SDL_Rect* dstrect);
int32_t encode_f (float f);

} } // end of namespace Freeworld:Integration

#endif // FREEWORLD_SDL_SYSTEM_HPP
