#include "keyboard.hpp"
#include <SDL.h>
#include <unordered_map>
#include <cstddef>

struct Key {
	bool is_down = false;
	uint16_t modifiers = 0;
};

static std::unordered_map<SDL_Keycode, Key> keymap;

bool get_key(SDL_Keycode k, int m) {
	switch (m) {
		case KMOD_NONE:
			return keymap[k].is_down;
		case -1:
			return keymap[k].is_down && keymap[k].modifiers == KMOD_NONE;
		default:
			return keymap[k].is_down && keymap[k].modifiers & m;
	}
}

void handle_keyevent(const SDL_KeyboardEvent& ke, bool is_down) {
	keymap[ke.keysym.sym].is_down = is_down;
	keymap[ke.keysym.sym].modifiers = ke.keysym.mod;
}
