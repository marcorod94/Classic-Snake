#ifndef ModuleSnake_h
#define ModuleSnake_h

#include "Module/Module.h"

struct Mix_Chunk;
struct SDL_FRect;
struct SDL_Rect;
struct SDL_Texture;
struct RenderObject;

constexpr int SNAKE_WIDTH = 30;
constexpr float DELTA_ANGLE = 90.F;
constexpr int MAX_SQUARE_WIDTH = SCREEN_WIDTH / SNAKE_WIDTH;
constexpr int MAX_SQUARE_HEIGHT = SCREEN_HEIGHT / SNAKE_WIDTH;
constexpr int POINT_VALUE = 5;
enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};



class ModuleSnake : public Module
{
public:
	explicit ModuleSnake(bool active = true);
	~ModuleSnake() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
	bool CheckCollision() const;
	void CreateFood();
	void AddBodyPart(const float2* position);
	void Reset();

	float speed = 0.5F;
	Uint32 startTime = 0;
	Uint32 deltaTime = 0;
	Uint32 delay = 10.F;
	float rotationAngle = 0.F;
	Mix_Chunk* dieSFX;
	Mix_Chunk* pointSFX;
	Direction currentDirection = Direction::RIGHT;
	RenderObject* head = nullptr;
	RenderObject* food = nullptr;
	std::vector<RenderObject*> snake;
	bool changeDirection = false;
};
#endif

