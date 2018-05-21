#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL.h>
#include "config.hpp"

enum class InitResult {
	Normal = 0,
	SDLInitializationError,
	SDLWindowCreationError,
	SDLRendererCreationError,
	ConfigError
};
InitResult init();

[[noreturn]]
void main_loop();

enum class QuitReason {
	Normal = 0,
	UnknownError,
	InitError
};
[[noreturn]]
void quit(QuitReason reason = QuitReason::Normal);

void handle_window_event(const SDL_WindowEvent&);

void create_default_config();

void set_fullscreen(bool);

#endif