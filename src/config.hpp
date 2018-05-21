#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Result.hpp"

struct Config {
	bool fullscreen = false;
	int width = 1, height = 1;
	char title[256] = "";
	bool vsync = false;
};

enum class ConfigError {
	None = 0,
	UnknownError,
	FileNotFound,
	InvalidValue
};
Result<Config, ConfigError> read_config(const char* path);

#endif