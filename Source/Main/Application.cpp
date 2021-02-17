#include "Application.h"
#include "Main/Globals.h"
#include "Game/ModulePlayScene.h"
#include "Game/ModuleScore.h"
#include "Game/ModuleSnake.h"
#include "Game/ModuleUI.h"
#include "Module/Module.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "Module/ModuleWindow.h"

Application::Application()
{
	modules.push_back(input = new ModuleInput());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(audio = new ModuleAudio());

	// Game
	modules.push_back(snake = new ModuleSnake(false));
	modules.push_back(score = new ModuleScore(false));
	modules.push_back(ui = new ModuleUI(false));
	modules.push_back(playScene = new ModulePlayScene());
}

Application::~Application()
{
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		delete* iterator;
	}
}

bool Application::Init() const
{
	bool value = true;
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->Init();
		}
	}
	return value;
}

UpdateStatus Application::Update() const {
	UpdateStatus value = UpdateStatus::CONTINUE;
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->PreUpdate();
		}
	}
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->Update();
		}
	}
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->PostUpdate();
		}
	}
	return value;
}

bool Application::CleanUp() const {
	bool value = true;
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->CleanUp();
		}
	}
	return value;
}