#ifndef ModuleRender_h
#define ModuleRender_h

#include "Module.h"

struct SDL_FRect;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

struct RenderObject
{
	SDL_Texture* texture = nullptr;
	SDL_FRect renderSection;
	SDL_Rect sourceSection;
};

class ModuleRender : public Module
{
public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

	ModuleRender();
	~ModuleRender() override = default;

	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;

	bool Blit(SDL_Texture* texture, SDL_FRect* renderSection, SDL_Rect* sourceSection = nullptr);
	bool Blit(SDL_Texture* texture, SDL_FRect* renderSection, float rotationAngle, SDL_Rect* sourceSection = nullptr);
};
#endif
