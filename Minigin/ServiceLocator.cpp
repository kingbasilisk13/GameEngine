#include "ServiceLocator.h"
#include "ISoundSystem.h"
#include "NullSoundSystem.h"

//dae::ServiceLocator::ServiceLocator()
//{
//	std::unique_ptr<ISoundSystem> ServiceLocator::m_SoundSystemInstance{ std::make_unique<NullSoundSystem>() };
//}

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
{
	/*if(soundSystem == nullptr)
	{
		m_SoundSystemInstance = std::make_unique<NullSoundSystem>();
	}
	else
	{
		m_SoundSystemInstance = std::move(soundSystem);
	}*/
	m_SoundSystemInstance = soundSystem == nullptr ? std::make_unique<NullSoundSystem>() : std::move(soundSystem);
}
