#include "Main/Application.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleScore.h"
#include "ModuleSnake.h"
#include "ModulePlayScene.h"
#include "ModuleUI.h"
#include "SDL.h"
#include "Utils/Collision.h"
#include "Utils/RandomGenerator.h"

ModuleSnake::ModuleSnake(bool active) : Module(active)
{

}

bool ModuleSnake::Init()
{
	Reset();
	dieSFX = App->audio->LoadFx("Assets/Audio/loose.wav");
	pointSFX = App->audio->LoadFx("Assets/Audio/point.wav");
	return true;
}

UpdateStatus ModuleSnake::Update()
{
	deltaTime += SDL_GetTicks() - startTime;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::DOWN && currentDirection != Direction::DOWN)
	{
		rotationAngle = DELTA_ANGLE;
		currentDirection = Direction::UP;
		changeDirection = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::DOWN && currentDirection != Direction::UP)
	{
		rotationAngle = 3 * DELTA_ANGLE;
		currentDirection = Direction::DOWN;
		changeDirection = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::DOWN && currentDirection != Direction::RIGHT)
	{
		rotationAngle = 2 * DELTA_ANGLE;
		currentDirection = Direction::LEFT;
		changeDirection = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::DOWN && currentDirection != Direction::LEFT)
	{
		rotationAngle = 0;
		currentDirection = Direction::RIGHT;
		changeDirection = true;
	}
	if (deltaTime >= delay * 100 || changeDirection)
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
		if (CheckCollision())
		{
			head->renderSection.x = lastPositon.x;
			head->renderSection.y = lastPositon.y;
			App->audio->PlayFx(dieSFX);
			Reset();
			App->ui->currentState = STATE::LOOSE;
			App->score->Reset();
		}
		else
		{
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
			if (Collision::IsOverLaping(&head->renderSection, &food->renderSection))
			{
				App->audio->PlayFx(pointSFX);
				AddBodyPart(&nextPositon);
				CreateFood();
				App->score->IncreseValue(POINT_VALUE);
			}
		}
		deltaTime = 0;
		startTime = SDL_GetTicks();
		changeDirection = false;
	}
	App->renderer->Blit(head->texture, &head->renderSection, rotationAngle, &head->sourceSection);
	for (auto body : snake)
	{
		App->renderer->Blit(body->texture, &body->renderSection, rotationAngle, &body->sourceSection);
	}
	App->renderer->Blit(food->texture, &food->renderSection, &food->sourceSection);
	return UpdateStatus::CONTINUE;
}

bool ModuleSnake::CleanUp()
{
	if (head)
	{
		App->texture->Unload(head->texture);
		delete head;
		head = nullptr;
	}
	if (food)
	{
		App->texture->Unload(food->texture);
		delete food;
		food = nullptr;
	}
	for (auto iterator = snake.begin(); iterator != snake.end(); ++iterator)
	{
		App->texture->Unload((*iterator)->texture);
		delete* iterator;
	}
	snake.clear();
	if (dieSFX)
	{
		App->audio->UnloadFx(dieSFX);
	}
	if (pointSFX)
	{
		App->audio->UnloadFx(dieSFX);
	}
	return true;
}

bool ModuleSnake::CheckCollision() const
{
	for (auto item : App->playScene->frame)
	{
		if (Collision::IsOverLaping(&head->renderSection, &item->renderSection))
		{
			return true;
		}
	}
	for (auto item : snake)
	{
		if (Collision::IsOverLaping(&head->renderSection, &item->renderSection))
		{
			return true;
		}
	}
	return false;
}
void ModuleSnake::CreateFood()
{
	bool isColliding = false;
	do
	{
		isColliding = false;
		float2 newPosition = float2(RandomGenerator::GetRandomNumber<float>(3, MAX_SQUARE_WIDTH - 3) * SNAKE_WIDTH,
			RandomGenerator::GetRandomNumber<float>(3, MAX_SQUARE_HEIGHT - 3) * SNAKE_WIDTH);
		this->food->renderSection.x = newPosition.x;
		this->food->renderSection.y = newPosition.y;
		if (Collision::IsOverLaping(&head->renderSection, &food->renderSection))
		{
			isColliding = true;
		}
		else
		{
			for (auto item : snake)
			{
				if (Collision::IsOverLaping(&item->renderSection, &food->renderSection))
				{
					isColliding = true;
					break;
				}
			}
		}

	} while (isColliding);
	
}

void ModuleSnake::AddBodyPart(const float2* position)
{
	auto part = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{position->x, position->y, SNAKE_WIDTH, SNAKE_WIDTH},
		{201, 540, 68, 68}

	};
	snake.push_back(part);
}

void ModuleSnake::Reset()
{
	snake.clear();
	head = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH * 3, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{674, 540, 68, 68}

	};
	float2 newPosition = float2(SNAKE_WIDTH * 2, 150);
	AddBodyPart(&newPosition);
	food = new RenderObject
	{
		App->texture->Load("Assets/Textures/snake.png"),
		{SNAKE_WIDTH, 150, SNAKE_WIDTH, SNAKE_WIDTH},
		{808, 878, 68, 66}

	};
	CreateFood();
	startTime = SDL_GetTicks();
	rotationAngle = 0;
	currentDirection = Direction::RIGHT;
}
