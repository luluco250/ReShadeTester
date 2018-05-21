# ReShade Tester

This is a minimal SDL2 program that uses it's hardware accelerated renderer to allow ReShade to inject itself, thus serving as a very simple test program for programming shaders.

You'll find useful ReShade shaders in the ```res``` folder, like displaying a full screen texture, which you can copy to whatever folder you use to store ReShade's shaders.

The program should work with ReShade set in DirectX 9 mode, ```d3d9.dll```, but you could try ```dxgi.dll``` or even ```opengl32.dll```.

The program will create a generic ```config.ini``` if one doesn't exist, so you can tweak settings like initial width/height, vsync etc.

This program targets ```C++17```, so build it with a compiler that's compatible with it.

You can press ```Alt```+```Enter``` to toggle fullscreen mode.
