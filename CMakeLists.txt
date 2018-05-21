cmake_minimum_required(VERSION 3.5)
project(MinimalReShadeTest)
set(CMAKE_CXX_STANDARD 17)

# Main Project
set(
	SOURCES
	${SOURCES}
	src/main.cpp
	src/keyboard.cpp
	src/config.cpp
)

add_executable(reshade_test WIN32 ${SOURCES})

# SDL2
set(SDL_SHARED OFF)
add_subdirectory(deps/sdl2)
include_directories(deps/sdl2/include)
target_link_libraries(reshade_test SDL2-static)
target_link_libraries(reshade_test SDL2main)
