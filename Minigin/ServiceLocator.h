#pragma once
#include <memory>

namespace dae
{
	class ISoundSystem;

	class ServiceLocator final
	{
		
	public:
		//ServiceLocator();

		static ISoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem);

	private:
		static std::unique_ptr<ISoundSystem> m_SoundSystemInstance;
	};
}
