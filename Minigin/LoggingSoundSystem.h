#pragma once
#include <memory>

#include "ISoundSystem.h"

namespace dae
{
	class LoggingSoundSystem final : public ISoundSystem
	{
	public:
		explicit LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem);

		~LoggingSoundSystem() override = default;

		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		void PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops) override;

		void PlayMusic(const sound_id id, const float volume, const int numberOfLoops) override;

		void PauseMusic() override;

		void ResumeMusic() override;

		void StopMusic() override;

		void Initialize(const std::string dataPath, const std::map<int, std::string> soundEffectList, const std::map<int, std::string> musicList) override;

	private:
		std::unique_ptr<ISoundSystem> m_RealSoundSystem;

		std::map<int, std::string> m_SoundEffectList;
		std::map<int, std::string> m_MusicList;

	};
}


