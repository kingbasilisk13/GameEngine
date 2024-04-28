#pragma once
#include "ISoundSystem.h"

namespace dae
{
	//an empty class to prevent null pointer exceptions
	class NullSoundSystem final : public ISoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;

		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;

		void PlaySoundEffect(const sound_id , const float , const int ) override{}

		void PlayMusic(const sound_id , const float , const int ) override {}

		void PauseMusic() override {}

		void ResumeMusic() override {}

		void StopMusic() override {}

		void Initialize(const std::string , const std::map<int, std::string> , const std::map<int, std::string> ) override{}
	};
}


