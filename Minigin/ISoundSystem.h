#pragma once
#include <map>
#include <string>

namespace dae
{
	using sound_id = unsigned short;
	class ISoundSystem
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;

		virtual void PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops) = 0;

		virtual void PlayMusic(const sound_id id, const float volume, const int numberOfLoops) = 0;

		virtual void PauseMusic() = 0;

		virtual void ResumeMusic() = 0;

		virtual void StopMusic() = 0;

		virtual void ToggleAudioMute() = 0;

		virtual void Initialize(const std::string dataPath, const std::map<int, std::string> soundEffectList, const std::map<int, std::string> musicList) = 0;
	};
}
