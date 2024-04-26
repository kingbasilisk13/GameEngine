#include "LoggingSoundSystem.h"

#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:m_RealSoundSystem(std::move(soundSystem))
{
}

void dae::LoggingSoundSystem::Play(const sound_id id, const float volume)
{
	m_RealSoundSystem->Play(id, volume);
	std::cout << "playing " << id << " at volume " << volume << "\n";
}
