#ifndef ModuleTexture_h
#define ModuleTexture_h

#include "Module.h"

struct SDL_Surface;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;

class ModuleTexture : public Module
{
public:
	ModuleTexture() = default;
	~ModuleTexture() override;

	bool Init() override;
	bool CleanUp() override;
	SDL_Texture* Load(const char* path);
	SDL_Texture* LoadText(const char* text, const float3* color);
	SDL_Surface* LoadSurface(const char* path);
	void Unload(const SDL_Texture* texture);

private:
	TTF_Font* font = nullptr;
	std::map<std::string, SDL_Texture*> textures;
};
#endif
