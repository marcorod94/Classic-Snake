#ifndef ModuleInput_h
#define ModuleInput_h

#include "Module.h"

constexpr int MAX_KEYS = 300;
constexpr int MOUSE_BUTTONS = 5;

enum class EventWindow
{
	QUIT = 0,
	HIDE,
	SHOW,
	COUNT
};

enum class KeyState
{
	IDLE,
	DOWN,
	REPEAT,
	UP
};

class ModuleInput : public Module
{
public:
	ModuleInput();
	~ModuleInput() override = default;
	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

	bool GetWindowEvent(EventWindow event) const;
	const float2& GetMousePosition() const;
	const float2& GetMouseMotion() const;
	const KeyState GetKey(const int id) const;
	const KeyState GetMouseButton(const int id) const;

private:
	std::vector<bool> windowEvents;
	std::vector <KeyState> keyboard;
	std::vector <KeyState> mouseButtons;
	float2 mousePosition = float2::zero;
	float2 mouseMotion = float2::zero;
	float2 mouseScroll = float2::zero;
	const Uint8* keys = nullptr;

	void ProcessKeyboardInput();
	void ProcessMouseButtons();
	void ProcessWindowEvents(Uint8 windowEvent);
};
#endif
