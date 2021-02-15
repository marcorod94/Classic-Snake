#include "Main/Application.h"
#include "ModulePlayScene.h"
#include "ModuleSnake.h"

ModulePlayScene::ModulePlayScene(bool active) : Module(active)
{

}

bool ModulePlayScene::Init()
{
	App->snake->Init();
	return true;
}
UpdateStatus ModulePlayScene::PreUpdate()
{
	return UpdateStatus::CONTINUE;
}
UpdateStatus ModulePlayScene::Update()
{
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