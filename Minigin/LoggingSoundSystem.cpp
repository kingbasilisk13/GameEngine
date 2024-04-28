#include "LoggingSoundSystem.h"

#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:m_RealSoundSystem(std::move(soundSystem))
{
}

void dae::LoggingSoundSystem::PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops)
{
	auto it = m_SoundEffectList.find(id);
	if(it == m_SoundEffectList.end())
	{
		std::cout << "ERROR: sound effect with ID " << id << " not found.\n";
		return;
	}
	m_RealSoundSystem->PlaySoundEffect(id, volume, numberOfLoops);
	std::cout << "playing " << m_SoundEffectList[id] << " at volume " << volume << "\n";
}

void dae::LoggingSoundSystem::PlayMusic(const sound_id id, const float volume, const int numberOfLoops)
{
	auto it = m_MusicList.find(id);
	if (it == m_MusicList.end())
	{
		std::cout << "ERROR: music with ID " << id << " not found.\n";
		return;
	}
	m_RealSoundSystem->PlayMusic(id, volume, numberOfLoops);
	std::cout << "playing " << m_MusicList[id] << " at volume " << volume << "\n";
}

void dae::LoggingSoundSystem::PauseMusic()
{
	m_RealSoundSystem->PauseMusic();
	std::cout << "PAUSE\n";
}

void dae::LoggingSoundSystem::ResumeMusic()
{
	m_RealSoundSystem->ResumeMusic();
	std::cout << "RESUME\n";
}

void dae::LoggingSoundSystem::StopMusic()
{
	m_RealSoundSystem->StopMusic();
	std::cout << "STOP\n";
}

void dae::LoggingSoundSystem::Initialize(const std::string dataPath, const std::map<int, std::string> soundEffectList, const std::map<int, std::string> musicList)
{
	m_SoundEffectList = soundEffectList;
	m_MusicList = musicList;
	m_RealSoundSystem->Initialize(dataPath, soundEffectList, musicList);
}
