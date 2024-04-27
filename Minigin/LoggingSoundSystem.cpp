#include "LoggingSoundSystem.h"

#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:m_RealSoundSystem(std::move(soundSystem))
{
}

void dae::LoggingSoundSystem::Play(const sound_id id, const float volume)
{
	m_RealSoundSystem->Play(id, volume);
	std::cout << "playing " << m_AudioList[id] << " at volume " << volume << "\n";
}

void dae::LoggingSoundSystem::Initialize(const std::string dataPath, const std::map<int, std::string> audioList)
{
	m_AudioList = audioList;

	m_RealSoundSystem->Initialize(dataPath, audioList);
}
