#include "Main/Application.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "Module/ModuleInput.h"
#include "ModuleUI.h"

#include "SDL.h"

ModuleUI::ModuleUI(bool active) : Module(active)
{

}

bool ModuleUI::Init()
{
	menuUI.push_back(new RenderObject {
		App->texture->LoadText("Classic Snake", new float3(255,0,0)),
		{(SCREEN_WIDTH - (SCREEN_WIDTH * 0.25F )) * 0.5F, SCREEN_HEIGHT * 0.25F, SCREEN_WIDTH * 0.25F, SCREEN_HEIGHT * 0.10F},
	});
	menuUI.push_back(new RenderObject{
		App->texture->LoadText("Press Enter to Start", new float3(255,0,0)),
		{(SCREEN_WIDTH - (SCREEN_WIDTH * 0.20F)) * 0.5F, SCREEN_HEIGHT * 0.5F, SCREEN_WIDTH * 0.20F, SCREEN_HEIGHT * 0.05F},
	});
	menuUI.push_back(new RenderObject{
		App->texture->LoadText("By marcorod94", new float3(255,0,0)),
		{(SCREEN_WIDTH - (SCREEN_WIDTH * 0.15F)) * 0.5F, SCREEN_HEIGHT * 0.6F, SCREEN_WIDTH * 0.15F, SCREEN_HEIGHT * 0.025F},
	});

	looseUI.push_back(new RenderObject{
		App->texture->LoadText("Game Over", new float3(255,0,0)),
		{(SCREEN_WIDTH - (SCREEN_WIDTH * 0.25F)) * 0.5F, SCREEN_HEIGHT * 0.3F, SCREEN_WIDTH * 0.25F, SCREEN_HEIGHT * 0.10F},
		});

	return true;
}
UpdateStatus ModuleUI::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KeyState::DOWN)
	{
		changeState = true;
	}
	if (currentState == STATE::MENU)
	{
		for (auto ui : menuUI)
		{
			App->renderer->Blit(ui->texture, &ui->renderSection);
		}
		if (changeState)
		{
			currentState = STATE::PLAY;
			changeState = false;
		}
	} 
	else if (currentState == STATE::WIN)
	{
		for (auto ui : winUI)
		{
			App->renderer->Blit(ui->texture, &ui->renderSection);
		}
		if (changeState)
		{
			currentState = STATE::MENU;
			changeState = false;
		}
	}
	else if (currentState == STATE::LOOSE)
	{
		for (auto ui : looseUI)
		{
			App->renderer->Blit(ui->texture, &ui->renderSection);
		}
		if (changeState)
		{
			currentState = STATE::MENU;
			changeState = false;
		}
	}
	return UpdateStatus::CONTINUE;
}
bool ModuleUI::CleanUp()
{
	for (auto iterator = menuUI.begin(); iterator != menuUI.end(); ++iterator)
	{
		App->texture->Unload((*iterator)->texture);
		delete* iterator;
	}
	menuUI.clear();
	for (auto iterator = winUI.begin(); iterator != winUI.end(); ++iterator)
	{
		App->texture->Unload((*iterator)->texture);
		delete* iterator;
	}
	winUI.clear();
	for (auto iterator = looseUI.begin(); iterator != looseUI.end(); ++iterator)
	{
		App->texture->Unload((*iterator)->texture);
		delete* iterator;
	}
	looseUI.clear();
	return true;
}