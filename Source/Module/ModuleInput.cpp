#include "ModuleInput.h"

#include "SDL.h"

ModuleInput::ModuleInput()
{
	windowEvents.resize(static_cast<int>(EventWindow::COUNT));
	mouseButtons.resize(MOUSE_BUTTONS);
	keyboard.resize(MAX_KEYS);

	std::fill(windowEvents.begin(), windowEvents.end(), false);
	std::fill(mouseButtons.begin(), mouseButtons.end(), KeyState::IDLE);
	std::fill(keyboard.begin(), keyboard.end(), KeyState::IDLE);
}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s", SDL_GetError());
		ret = false;
	}
	return ret;
}

UpdateStatus ModuleInput::PreUpdate()
{

	static SDL_Event event;

	mouseMotion = float2::zero;
	std::fill(windowEvents.begin(), windowEvents.end(), false);

	keys = SDL_GetKeyboardState(nullptr);

	ProcessKeyboardInput();
	ProcessMouseButtons();

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				windowEvents[static_cast<int>(EventWindow::QUIT)] = true;
				break;

			case SDL_WINDOWEVENT:
				ProcessWindowEvents(event.window.event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseButtons[event.button.button - 1] = KeyState::DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseButtons[event.button.button - 1] = KeyState::UP;
				break;

			case SDL_MOUSEMOTION:
				mouseMotion.x = static_cast<float>(event.motion.xrel);
				mouseMotion.y = static_cast<float>(event.motion.yrel);
				mousePosition.x = static_cast<float>(event.motion.x);
				mousePosition.y = static_cast<float>(event.motion.y);
				break;
			default:
				break;
		}
	}
	if (GetWindowEvent(EventWindow::QUIT)|| GetKey(SDL_SCANCODE_ESCAPE) == KeyState::DOWN)
	{
		return UpdateStatus::STOP;
	}
	return  UpdateStatus::CONTINUE;
}

UpdateStatus ModuleInput::Update()
{
	SDL_PumpEvents();
	return UpdateStatus::CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

bool ModuleInput::GetWindowEvent(EventWindow event) const
{
	return windowEvents[static_cast<int>(event)];
}

const float2& ModuleInput::GetMousePosition() const
{
	return mousePosition;
}

const float2& ModuleInput::GetMouseMotion() const
{
	return mouseMotion;
}

const KeyState ModuleInput::GetKey(const int id) const
{
	return keyboard[id];
}

const KeyState ModuleInput::GetMouseButton(const int id) const
{
	return mouseButtons[id - 1];
}

void ModuleInput::ProcessKeyboardInput()
{
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KeyState::IDLE)
			{
				keyboard[i] = KeyState::DOWN;
			}
			else
			{
				keyboard[i] = KeyState::REPEAT;
			}
		}
		else
		{
			if (keyboard[i] == KeyState::REPEAT || keyboard[i] == KeyState::DOWN)
			{
				keyboard[i] = KeyState::UP;
			}
			else
			{
				keyboard[i] = KeyState::IDLE;
			}
		}
	}
}

void ModuleInput::ProcessMouseButtons()
{
	for (int i = 0; i < MOUSE_BUTTONS; ++i)
	{
		if (mouseButtons[i] == KeyState::DOWN)
		{
			mouseButtons[i] = KeyState::REPEAT;
		}

		if (mouseButtons[i] == KeyState::UP)
		{
			mouseButtons[i] = KeyState::IDLE;
		}
	}
}

void ModuleInput::ProcessWindowEvents(Uint8 windowEvent)
{
	switch (windowEvent)
	{
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_FOCUS_LOST:
			windowEvents[static_cast<int>(EventWindow::HIDE)] = true;
			break;

		case SDL_WINDOWEVENT_SHOWN:
		case SDL_WINDOWEVENT_FOCUS_GAINED:
		case SDL_WINDOWEVENT_MAXIMIZED:
		case SDL_WINDOWEVENT_RESTORED:
			windowEvents[static_cast<int>(EventWindow::SHOW)] = true;
			break;
		default:
			break;
	}
}
