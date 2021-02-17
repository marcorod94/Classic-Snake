#include "Main/Application.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleScore.h"

ModuleScore::ModuleScore(bool active) : Module(active)
{

}

bool ModuleScore::Init()
{
	unit = new RenderObject {
		nullptr,
		{SCREEN_WIDTH * 0.96F, 10, SCREEN_WIDTH * 0.04F, SCREEN_HEIGHT * 0.04F},
	};
	ten = new RenderObject {
		nullptr,
		{SCREEN_WIDTH * 0.92F, 10, SCREEN_WIDTH * 0.04F, SCREEN_HEIGHT * 0.04F}
	};
	cent = new RenderObject {
		nullptr,
		{SCREEN_WIDTH * 0.88F, 10, SCREEN_WIDTH * 0.04F, SCREEN_HEIGHT * 0.04F}
	};
	numberTextures.push_back(App->texture->LoadText("0", &color));
	numberTextures.push_back(App->texture->LoadText("1", &color));
	numberTextures.push_back(App->texture->LoadText("2", &color));
	numberTextures.push_back(App->texture->LoadText("3", &color));
	numberTextures.push_back(App->texture->LoadText("4", &color));
	numberTextures.push_back(App->texture->LoadText("5", &color));
	numberTextures.push_back(App->texture->LoadText("6", &color));
	numberTextures.push_back(App->texture->LoadText("7", &color));
	numberTextures.push_back(App->texture->LoadText("8", &color));
	numberTextures.push_back(App->texture->LoadText("9", &color));

	unit->texture = numberTextures[0];
	ten->texture = numberTextures[0];
	cent->texture = numberTextures[0];

	return true;
}

UpdateStatus ModuleScore::Update()
{
	App->renderer->Blit(unit->texture, &unit->renderSection);
	App->renderer->Blit(ten->texture, &ten->renderSection);
	App->renderer->Blit(cent->texture, &cent->renderSection);
	return UpdateStatus::CONTINUE;
}

bool ModuleScore::CleanUp()
{
	if (unit)
	{
		delete unit;
		unit = nullptr;
	}
	if (ten)
	{
		delete ten;
		ten = nullptr;
	}
	if (cent)
	{
		delete cent;
		cent = nullptr;
	}

	for (auto iterator = numberTextures.begin(); iterator != numberTextures.end(); ++iterator)
	{
		App->texture->Unload(*iterator);
		delete* iterator;
	}
	numberTextures.clear();
	value = 0;
	return true;
}

void ModuleScore::IncreseValue(int amount)
{
	value += amount;
	int number = value;
	unit->texture = numberTextures[number % 10];
	number = number / 10;
	ten->texture = numberTextures[number % 10];
	number = number / 10;
	cent->texture = numberTextures[number % 10];
}

void ModuleScore::Reset()
{
	value = 0;
	unit->texture = numberTextures[0];
	ten->texture = numberTextures[0];
	cent->texture = numberTextures[0];
}