#include "config.hpp"

#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include "Result.hpp"

std::string get_trimmed(const std::string& str) {
	auto start = str.find_first_not_of(" \t");
	auto stop = str.find_last_not_of(" \t");

	return str.substr(start, stop - start + 1);
}

Result<Config, ConfigError> read_config(const char* path) {
	static const std::regex regex_config(R"((.+)=(.*))");

	std::ifstream config_file(path);
	if (!config_file.is_open())
		return ConfigError::FileNotFound;

	Config config;
	std::smatch match;
	std::string name, value;

	for (std::string line; std::getline(config_file, line);) {
		// Remove comments
		auto comment_pos = line.find_first_of("#;");
		if (comment_pos != line.npos)
			line.erase(comment_pos);

		if (std::regex_match(line, match, regex_config)) {
			name = get_trimmed(match[1]);
			value = get_trimmed(match[2]);

			if (name == "width") {
				try {
					config.width = std::stoi(value);
				} catch (...) {
					return ConfigError::InvalidValue;
				}
			} else if (name == "height") {
				try {
					config.height = std::stoi(value);
				} catch (...) {
					return ConfigError::InvalidValue;
				}
			} else if (name == "vsync") {
				// Make 'value' all lowercase
				std::transform(value.begin(), value.end(), value.begin(), tolower);

				if (value == "true")
					config.vsync = true;
				else if (value == "false")
					config.vsync = false;
				else
					return ConfigError::InvalidValue;
			} else if (name == "title") {
				auto begin = value.find_first_not_of("\"'");
				auto end = value.find_last_not_of("\"'");

				std::string no_quotes = value.substr(begin, end - begin + 1);

				strcpy_s(config.title, no_quotes.c_str());
			} else if (name == "fullscreen") {
				std::transform(value.begin(), value.end(), value.begin(), tolower);

				if (value == "true")
					config.fullscreen = true;
				else if (value == "false")
					config.fullscreen = false;
				else
					return ConfigError::InvalidValue;
			}
		}
	}

	return config;
}
