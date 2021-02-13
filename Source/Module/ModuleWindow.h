#ifndef ModuleWindow_h
#define ModuleWindow_h

#include "Module.h"

struct SDL_Surface;
struct SDL_Window;

class ModuleWindow : public Module
{
public:
	SDL_Window* window = nullptr;
	SDL_Surface* screenIcon = nullptr;
	SDL_Surface* screenSurface = nullptr;

	ModuleWindow() = default;
	~ModuleWindow() override = default;
	bool Init() override;
	bool CleanUp() override;
};
#endif
