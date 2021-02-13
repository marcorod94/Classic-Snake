#include "Main/Application.h"
#include "Main/Globals.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

#include "SDL.h"

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

UpdateStatus ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleRender::Update()
{
	int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::REPEAT)
	{
		App->renderer->camera.y += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::REPEAT)
	{
		App->renderer->camera.y -= speed;
	}	

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::REPEAT)
	{
		App->renderer->camera.x += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::REPEAT)
	{
		App->renderer->camera.x -= speed;
	}

	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UpdateStatus::CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, SDL_FRect* renderSection, SDL_Rect* sourceSection)
{
	bool ret = true;
	if (SDL_RenderCopyF(renderer, texture, sourceSection, renderSection) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}
	return ret;
}
