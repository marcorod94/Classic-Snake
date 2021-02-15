#include "Main/Application.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleSnake.h"
#include "ModulePlayScene.h"
#include "SDL.h"
#include "Utils/Collision.h"

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
	food = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{808, 878, 68, 68}

	};
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
			head->renderSection.x -= SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::RIGHT)
		{
			head->renderSection.x += SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::UP)
		{
			head->renderSection.y -= SNAKE_WIDTH;
		}
		else if (currentDirection == Direction::DOWN)
		{
			head->renderSection.y += SNAKE_WIDTH;
		}
		// Check Collisions with borders Body and food
		App->renderer->Blit(head->texture, &head->renderSection, rotationAngle, &head->sourceSection);
		
		for (auto body : snake)
		{
			lastPositon.x = body->renderSection.x;
			lastPositon.y = body->renderSection.y;
			body->renderSection.x = nextPositon.x;
			body->renderSection.y = nextPositon.y;
			nextPositon = lastPositon;
			App->renderer->Blit(body->texture, &body->renderSection, rotationAngle, &body->sourceSection);
		}
		deltaTime = 0;
		startTime = SDL_GetTicks();
	}
	App->renderer->Blit(head->texture, &head->renderSection, rotationAngle, &head->sourceSection);
	for (auto body : snake)
	{
		App->renderer->Blit(body->texture, &body->renderSection, rotationAngle, &body->sourceSection);
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

bool ModuleSnake::CheckCollision()
{
	for (auto item : App->playScene->frame)
	{

		if (Collision::IsOverLaping(&head->renderSection, &item->renderSection))
		{
			return true;
		}
	}
	return true;
}