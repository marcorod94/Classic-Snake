#ifndef ModuleAudio_h
#define ModuleAudio_h

#include "Module.h"

constexpr float DEFAULT_MUSIC_FADE_TIME = 2.0F;

struct _Mix_Music;
struct Mix_Chunk;
using Mix_Music = _Mix_Music;

class ModuleAudio : public Module
{
public:
	ModuleAudio() = default;
	~ModuleAudio() override = default;

	bool Init() override;
	bool CleanUp() override;

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	Mix_Chunk* LoadFx(const char* path);
	bool PlayFx(Mix_Chunk* sfx, int repeat = 0) const;
	void UnloadFx(const Mix_Chunk* sfx);

private:

	Mix_Music* music = nullptr;
	std::map<std::string, Mix_Chunk*>	soundEffects;
};
#endif
