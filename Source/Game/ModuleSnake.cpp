#include "Main/Application.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleSnake.h"
#include "SDL.h"

ModuleSnake::ModuleSnake(bool active) : Module(active)
{

}

bool ModuleSnake::Init()
{
	head = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH * 2, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{674, 540, 68, 68}

	};
	RenderObject* part = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{201, 540, 68, 68}

	};
	RenderObject* part = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{808, 829, 68, 68}

	};
	snake.push_back(head);
	snake.push_back(part);
	startTime = SDL_GetTicks();
	return true;
}
UpdateStatus ModuleSnake::PreUpdate()
{
	return UpdateStatus::CONTINUE;
}
UpdateStatus ModuleSnake::Update()
{
	deltaTime += SDL_GetTicks() - startTime;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::DOWN && currentDirection != Direction::DOWN)
	{
		rotationAngle = DELTA_ANGLE;
		currentDirection = Direction::UP;
		deltaTime = delay * 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::DOWN && currentDirection != Direction::UP)
	{
		rotationAngle = 3 * DELTA_ANGLE;
		currentDirection = Direction::DOWN;
		deltaTime = delay * 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::DOWN && currentDirection != Direction::RIGHT)
	{
		rotationAngle = 2 * DELTA_ANGLE;
		currentDirection = Direction::LEFT;
		deltaTime = delay * 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::DOWN && currentDirection != Direction::LEFT)
	{
		rotationAngle = 0;
		currentDirection = Direction::RIGHT;
		deltaTime = delay * 1000;
	}
	if (deltaTime >= delay * 1000)
	{
		float2 lastPositon = float2(head->renderSection.x, head->renderSection.y);
		float2 nextPositon = lastPositon;
		if (currentDirection == Direction::LEFT)
		{
			nextPositon.x -= SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::RIGHT)
		{
			nextPositon.x += SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::UP)
		{
			nextPositon.y -= SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::DOWN)
		{
			nextPositon.y += SNAKE_WIDTH;
		}

		for (auto body : snake)
		{
			lastPositon.x = body->renderSection.x;
			lastPositon.y = body->renderSection.y;
			body->renderSection.x = nextPositon.x;
			body->renderSection.y = nextPositon.y;
			nextPositon = lastPositon;
			App->renderer->Blit(body->texture, &body->renderSection, &body->sourceSection, rotationAngle);
		}
		deltaTime = 0;
		startTime = SDL_GetTicks();
	}
	for (auto body : snake)
	{
		App->renderer->Blit(body->texture, &body->renderSection, &body->sourceSection, rotationAngle);
	}
	return UpdateStatus::CONTINUE;
}
UpdateStatus ModuleSnake::PostUpdate()
{
	return UpdateStatus::CONTINUE;
}
bool ModuleSnake::CleanUp()
{
	return true;
}