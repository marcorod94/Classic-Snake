#ifndef Animation_H
#define Animation_H

#include <vector>

struct SDL_Rect;

class Animation
{
public:
	float speed = 1.F;
	std::vector<SDL_Rect> frames;

	Animation() = default;
	SDL_Rect& GetCurrentFrame()
	{
		currentFrame += speed;
		if (currentFrame >= static_cast<float>(frames.size()))
		{
			currentFrame = 0.F;
		}
		return frames[(int)currentFrame];
	}

private:
	float currentFrame = 0.F;
};
#endif
