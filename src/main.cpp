#include "main.hpp"
#include <SDL.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "keyboard.hpp"
#include "config.hpp"

static SDL_Window* window;
static SDL_Renderer* renderer;
static Config* config;
static SDL_DisplayMode display_mode;

int main(int argc, char** argv) {
	switch (init()) {
		case InitResult::Normal:
			main_loop();
			break; // Should never break, but let's be safe.
		case InitResult::SDLInitializationError:
			fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
			break;
		case InitResult::SDLWindowCreationError:
			fprintf(stderr, "Failed to create SDL_Window: %s\n", SDL_GetError());
			break;
		case InitResult::SDLRendererCreationError:
			fprintf(stderr, "Failed to create SDL_Renderer: %s\n", SDL_GetError());
			break;
		case InitResult::ConfigError:
			fputs("Failed to read configuration file!\n", stderr);
			break;
	}

	quit(QuitReason::InitError);
}

InitResult init() {
	auto config_res = read_config("config.ini");

	if (!config_res) {
		if (config_res.error() == ConfigError::FileNotFound) {
			create_default_config();
		} else {
			return InitResult::ConfigError;
		}
	}

	config = new Config{*config_res};

	SDL_GetDisplayMode(0, 0, &display_mode);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return InitResult::SDLInitializationError;

	window = SDL_CreateWindow(
		config->title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		config->width,
		config->height,
		SDL_WINDOW_RESIZABLE
	);
	if (!window)
		return InitResult::SDLWindowCreationError;

	long renderer_flags = SDL_RENDERER_ACCELERATED;
	if (config->vsync)
		renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
	
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (!renderer)
		return InitResult::SDLRendererCreationError;

	SDL_RenderSetLogicalSize(renderer, config->width, config->height);

	if (config->fullscreen)
		set_fullscreen(config->fullscreen);
	
	return InitResult::Normal;
}

void main_loop() {
	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					quit();
					break;
				case SDL_WINDOWEVENT:
					handle_window_event(e.window);
					break;
				case SDL_KEYDOWN:
					handle_keyevent(e.key, true);
					break;
				case SDL_KEYUP:
					handle_keyevent(e.key, false);
					break;
			}
		}

		if (get_key(SDLK_RETURN, KMOD_ALT)) {
			set_fullscreen(!config->fullscreen);
			config->fullscreen = !config->fullscreen;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}

void handle_window_event(const SDL_WindowEvent& we) {
	switch (we.event) {
		case SDL_WINDOWEVENT_RESIZED:
			SDL_RenderSetLogicalSize(renderer, we.data1, we.data2);
			break;
	}
}

void quit(QuitReason reason) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(static_cast<int>(reason));
}

void create_default_config() {
	strcpy_s(config->title, "ReShade Tester");
	config->width = 640;
	config->height = 480;
	config->vsync = true;

	std::ofstream config_file("config.ini");
	config_file << 
R"(
[Configurations]
title = "ReShade Tester"
width = 640
height = 480
vsync = true
fullscreen = false
)";
}

void set_fullscreen(bool b) {
	if (b) { // Fullscreen
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(renderer, display_mode.w, display_mode.h);
	} else { // Windowed
		SDL_SetWindowFullscreen(window, 0);
		SDL_RenderSetLogicalSize(renderer, config->width, config->height);
	}
}
