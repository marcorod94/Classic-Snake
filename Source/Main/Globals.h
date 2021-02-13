#ifndef Globals_h
#define Globals_h

#include "MathGeoLib.h"
#include "SDL_rect.h"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum class UpdateStatus
{
	CONTINUE = 1,
	STOP,
	ERROR
};

constexpr bool VSYNC = true;
constexpr int SCREEN_WIDTH = 480;
constexpr int SCREEN_HEIGHT = 720;
constexpr bool FULLSCREEN = false;
constexpr bool RESIZABLE = true;
constexpr const char* TITLE = "GameTemplate";
#endif
