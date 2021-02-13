#include "ModuleAudio.h"

#include "SDL.h"
#include "SDL_mixer.h"

bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	for (auto iterator = soundEffects.begin(); iterator != soundEffects.end(); ++iterator)
	{
		Mix_FreeChunk((*iterator).second);
	}

	soundEffects.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

Mix_Chunk* ModuleAudio::LoadFx(const char* path)
{
	auto iterator = soundEffects.find(path);
	if (iterator != soundEffects.end())
	{
		return (*iterator).second;
	}

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		soundEffects.emplace(std::make_pair(path, chunk));
	}

	return chunk;
}

bool ModuleAudio::PlayFx(Mix_Chunk* sfx, int repeat) const
{
	bool ret = false;

	if (sfx != nullptr)
	{
		Mix_PlayChannel(-1, sfx, repeat);
		ret = true;
	}

	return ret;
}

void ModuleAudio::UnloadFx(const Mix_Chunk* sfx)
{
	for (auto iterator = soundEffects.begin(); iterator != soundEffects.end(); ++iterator)
	{

		if ((*iterator).second == sfx)
		{
			Mix_FreeChunk((*iterator).second);
			soundEffects.erase(iterator);
			break;
		}
	}
}