#include "Application.h"
#include "Globals.h"

#include "SDL.h"

#include <iostream>

enum class MainState
{
	CREATION,
	START,
	UPDATE,
	FINISH,
	EXIT
};

Application* App = nullptr;

int main(int argc, char* args[])
{
	int mainReturn = EXIT_FAILURE;
	MainState state = MainState::CREATION;

	while (state != MainState::EXIT)
	{
		switch (state)
		{
			case MainState::CREATION:
				App = new Application();
				state = MainState::START;
				break;
			case MainState::START:
				if (App->Init() == false)
				{
					state = MainState::EXIT;
				}
				else
				{
					state = MainState::UPDATE;
				}
				break;
			case MainState::UPDATE:
			{
				UpdateStatus updateReturn = App->Update();

				if (updateReturn == UpdateStatus::ERROR)
				{
					state = MainState::EXIT;
				}
				else if (updateReturn == UpdateStatus::STOP)
				{
					state = MainState::FINISH;
				}
			}
			break;
			case MainState::FINISH:
				if (App->CleanUp()) 
				{
					mainReturn = EXIT_SUCCESS;
				}
				state = MainState::EXIT;
				break;
			default:
				state = MainState::EXIT;
				break;
		}
	}
	delete App;
	return mainReturn;
}
