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


		void Play(const sound_id id, const float volume) override;

		void Initialize(const std::string dataPath, const std::map<int, std::string> audioList) override;

	private:
		class MixerImpl;
		MixerImpl* m_Pimpl{};
	};
}


