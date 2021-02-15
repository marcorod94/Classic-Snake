#ifndef ModulePlayScene_h
#define ModulePlayScene_h

#include "Module/Module.h"

class ModulePlayScene : public Module
{
public:
	explicit ModulePlayScene(bool active = true);
	~ModulePlayScene() override = default;
	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;
};
#endif
