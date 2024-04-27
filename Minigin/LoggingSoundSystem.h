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

		void Play(const sound_id id, const float volume) override;

		void Initialize(const std::string dataPath, const std::map<int, std::string> audioList) override;

	private:
		std::unique_ptr<ISoundSystem> m_RealSoundSystem;

		std::map<int, std::string> m_AudioList;

	};
}


