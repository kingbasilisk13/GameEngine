#include "ServiceLocator.h"
#include "ISoundSystem.h"
#include "NullSoundSystem.h"

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
{
	
	if(soundSystem == nullptr)
	{
		m_SoundSystemInstance = std::make_unique<NullSoundSystem>();
	}
	else
	{
		m_SoundSystemInstance = std::move(soundSystem);
	}
}
