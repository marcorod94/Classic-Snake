#ifndef ModuleSnake_h
#define ModuleSnake_h

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Rect;
struct SDL_Texture;

constexpr int SNAKE_WIDTH = 30;
constexpr float DELTA_ANGLE = 90.f;
enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct RenderObject
{
	SDL_Texture* texture = nullptr;
	SDL_FRect renderSection;
	SDL_Rect sourceSection;
};

class ModuleSnake : public Module
{
public:
	explicit ModuleSnake(bool active = true);
	~ModuleSnake() override = default;
	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;

	float speed = 0.5f;
	Uint32 startTime = 0;
	Uint32 deltaTime = 0;
	Uint32 delay = 20.f;
	float rotationAngle = 0.f;
	Direction currentDirection = Direction::RIGHT;
	RenderObject* head = nullptr;
	RenderObject* food = nullptr;
	std::vector<RenderObject*> snake;
};
#endif

