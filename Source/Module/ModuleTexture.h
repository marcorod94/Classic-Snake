#ifndef ModuleTexture_h
#define ModuleTexture_h

#include "Module.h"

struct SDL_Surface;
struct SDL_Texture;

class ModuleTexture : public Module
{
public:
	ModuleTexture() = default;
	~ModuleTexture() override;

	bool Init() override;
	bool CleanUp() override;
	SDL_Texture* Load(const char* path);
	SDL_Surface* LoadSurface(const char* path);
	void Unload(const SDL_Texture* texture);

private:
	std::map<std::string, SDL_Texture*> textures;
};
#endif
