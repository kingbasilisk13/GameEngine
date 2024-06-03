#pragma once
#include <memory>

#include "ISoundSystem.h"

namespace dae
{

	class SdlSoundSystem final: public ISoundSystem
	{
	public:
		SdlSoundSystem() = default;
		~SdlSoundSystem() override;

		SdlSoundSystem(const SdlSoundSystem& other) = delete;
		SdlSoundSystem(SdlSoundSystem&& other) = delete;
		SdlSoundSystem& operator=(const SdlSoundSystem& other) = delete;
		SdlSoundSystem& operator=(SdlSoundSystem&& other) = delete;

		void PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops) override;

		void PlayMusic(const sound_id id, const float volume, const int numberOfLoops) override;

		void PauseMusic() override;

		void ResumeMusic() override;

		void StopMusic() override;

		void ToggleAudioMute() override;

		void Initialize(const std::string dataPath, const std::map<int, std::string> soundEffectList, const std::map<int, std::string> musicList) override;

	private:
		class MixerImpl;
		MixerImpl* m_Pimpl{};
	};
}


/*
 *  
 */