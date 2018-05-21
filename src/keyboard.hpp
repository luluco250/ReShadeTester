#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL.h>

void handle_keyevent(const SDL_KeyboardEvent&, bool is_down);
bool get_key(SDL_Keycode, int modifier = KMOD_NONE);

#endif