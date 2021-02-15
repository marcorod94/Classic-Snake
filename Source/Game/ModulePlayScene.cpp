#include "Main/Application.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModulePlayScene.h"
#include "ModuleSnake.h"

ModulePlayScene::ModulePlayScene(bool active) : Module(active)
{

}

bool ModulePlayScene::Init()
{
	frame.push_back(new RenderObject{
		App->texture->Load("Assets/Textures/snake.png"),
		{0, 0, SNAKE_WIDTH, SCREEN_HEIGHT},
		{0, 0, 68, 1075}
	});
	frame.push_back(new RenderObject{
		App->texture->Load("Assets/Textures/snake.png"),
		{SCREEN_WIDTH - SNAKE_WIDTH, 0, SNAKE_WIDTH, SCREEN_HEIGHT},
		{1007, 0, 68, 1075}
	});
	frame.push_back(new RenderObject{
		App->texture->Load("Assets/Textures/snake.png"),
		{0 , 0, SCREEN_WIDTH, SNAKE_WIDTH},
		{0, 0, 1075, 68}
	});
	frame.push_back(new RenderObject{
		App->texture->Load("Assets/Textures/snake.png"),
		{0, SNAKE_WIDTH - SCREEN_HEIGHT, SCREEN_WIDTH , SNAKE_WIDTH},
		{0, 1007, 1075, 68}
	});
	App->snake->Init();
	return true;
}
UpdateStatus ModulePlayScene::PreUpdate()
{
	return UpdateStatus::CONTINUE;
}
UpdateStatus ModulePlayScene::Update()
{
	for (auto item : frame)
	{
		App->renderer->Blit(item->texture, &item->renderSection, &item->sourceSection);
	}
	App->snake->Update();
	return UpdateStatus::CONTINUE;
}
UpdateStatus ModulePlayScene::PostUpdate()
{
	return UpdateStatus::CONTINUE;
}
bool ModulePlayScene::CleanUp()
{
	App->snake->CleanUp();
	return true;
}