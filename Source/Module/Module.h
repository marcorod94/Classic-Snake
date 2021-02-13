#ifndef Module_h
#define Module_h

#include "Main/Globals.h"

class Module
{
public:
	bool enableNextFrame = false;

	explicit Module(bool active = true) : active(active){}
	virtual ~Module() = default;

	virtual bool Init()
	{
		return true;
	}

	virtual UpdateStatus PreUpdate()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual UpdateStatus Update()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual UpdateStatus PostUpdate()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	bool IsEnabled() const
	{
		return active;
	}

	void Enable()
	{
		if (active == false)
		{
			active = Init();
		}
	}

	void Disable()
	{
		if (active)
		{
			active = !CleanUp();
		}
	}

private:
	bool active = true;
};
#endif
