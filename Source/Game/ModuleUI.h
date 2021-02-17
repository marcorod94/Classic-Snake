#ifndef ModuleUI_H
#define ModuleUI_H

#include "Module/Module.h"

struct RenderObject;

enum class STATE {
	MENU,
	PLAY,
	WIN,
	LOOSE
};

class ModuleUI : public Module
{
public:
	explicit ModuleUI(bool active = true);
	~ModuleUI() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

	STATE currentState = STATE::MENU;

	std::vector<RenderObject*> menuUI;
	std::vector<RenderObject*> winUI;
	std::vector<RenderObject*> looseUI;
	bool changeState = false;
};
#endif
