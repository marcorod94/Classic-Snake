#ifndef Collision_H
#define Collision_H

#include "SDL.h"

class Collision
{
public:
	bool static IsOverLaping(const SDL_Rect* source, const SDL_Rect* target)
	{
		return source->x < target->x + target->w &&
			source->x + source->w > target->x &&
			source->y < target->y + target->h &&
			source->y + source->h > target->y;
	}

	bool static IsOverLaping(const SDL_FRect* source, const SDL_FRect* target)
	{
		return source->x < target->x + target->w &&
			source->x + source->w > target->x &&
			source->y < target->y + target->h &&
			source->y + source->h > target->y;
	}
};
#endif
