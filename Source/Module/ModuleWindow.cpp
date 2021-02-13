#include "Main/Application.h"
#include "ModuleTexture.h"
#include "ModuleWindow.h"
#include "SDL.h"

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		if (FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (RESIZABLE)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			screenIcon = App->texture->LoadSurface("Assets/Icon/icon.png");
			if (screenIcon)
			{
				SDL_SetWindowIcon(window, screenIcon);
			}
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return true;
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");
	if (window != nullptr)
	{
		SDL_FreeSurface(screenIcon);
		SDL_FreeSurface(screenSurface);
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return true;
}
