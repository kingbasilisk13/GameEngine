#include "SdlSoundSystem.h"
#include "SDL_mixer.h"

dae::SdlSoundSystem::~SdlSoundSystem()
{
    Mix_FreeMusic(music);
}

void dae::SdlSoundSystem::Play(const sound_id , const float )
{
    //Initialize SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return;
    }
	music = Mix_LoadMUS("../Data/Sound/01 Credit Sound.mp3");
    if (music == NULL)
    {
        return;
    }

    Mix_PlayMusic(music, -1);
}
