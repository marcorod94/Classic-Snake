#ifndef ModuleScore_H
#define ModuleScore_H

#include "Module/Module.h"


struct RenderObject;
struct SDL_Texture;

class ModuleScore : public Module
{
public:
	int value = 0;
	std::vector<SDL_Texture*> numberTextures;

	RenderObject* cent = nullptr;
	RenderObject* ten = nullptr;
	RenderObject* unit = nullptr;
	float3 color = float3(255, 255, 255);

	explicit ModuleScore(bool active = true);
	~ModuleScore() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
	void Reset();

	void IncreseValue(int amount = 1);
};
#endif
