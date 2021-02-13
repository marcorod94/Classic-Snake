#ifndef Application_h
#define Application_h

#include <vector>

class Module;
class ModuleAudio;
class ModuleInput;
class ModuleRender;
class ModuleTexture;
class ModuleWindow;
enum class UpdateStatus;

class Application {
public:
	ModuleInput* input = nullptr;
	ModuleWindow* window = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleAudio* audio = nullptr;

	Application();
	~Application();

	bool Init() const;
	UpdateStatus Update() const;
	bool CleanUp() const;

private:
	std::vector<Module*> modules;
};
extern Application* App;
#endif