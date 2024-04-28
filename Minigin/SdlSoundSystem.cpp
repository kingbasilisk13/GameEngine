#include "SdlSoundSystem.h"
#include <iostream>
#include <mutex>
#include <queue>
#include <ranges>
#include <thread>

#include "SDL_mixer.h"


struct SoundDataStruct
{
    bool quit = false;
    Mix_Chunk* music;
	float volume;
    int loop;
    
};


#pragma region PIMPL
class dae::SdlSoundSystem::MixerImpl
{
public:
    MixerImpl() = default;

    ~MixerImpl()
    {
        {
            std::lock_guard<std::mutex> lock(m_Mutex);

            m_EventQueue.push(
                {
                    true,
                    nullptr,
                    0,
                    0
                });

            m_ConditionVariable.notify_all();
        }

        m_SoundThread.join();

        for (const auto& snd : m_SoundEffectList | std::views::values)
        {
            Mix_FreeChunk(snd);
        }

        for (const auto& snd : m_MusicList | std::views::values)
        {
            Mix_FreeMusic(snd);
        }

        Mix_CloseAudio();
        
    }

    MixerImpl(const MixerImpl& other) = delete;
    MixerImpl(MixerImpl&& other) = delete;
    MixerImpl& operator=(const MixerImpl& other) = delete;
    MixerImpl& operator=(MixerImpl&& other) = delete;

    void Initialize(const std::string& dataPath, const std::map<int, std::string>& soundEffectList, const std::map<int, std::string>& musicList)
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cout << "ERROR: unable to initialize SDL_mixer";
            return;
        }

        for (const auto& [fst, snd] : soundEffectList)
        {
            LoadInSoundEffect(fst, dataPath + snd);
        }

        for (const auto& [fst, snd] : musicList)
        {
            LoadInMusic(fst, dataPath + snd);
        }

        m_SoundThread = std::jthread(&MixerImpl::InfiniteLoop, this);
    }

    //pushes sound event to queue
    void PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops)
    {
	    if (const auto it = m_SoundEffectList.find(id); it == m_SoundEffectList.end()) 
        {
            return;
        }

        std::lock_guard<std::mutex> lock(m_Mutex);

        m_EventQueue.push(
            {
                false,
                m_SoundEffectList[id],
                volume,
                numberOfLoops
            });

        m_ConditionVariable.notify_one();
    }

    void PlayMusic(const sound_id id, const float volume, const int numberOfLoops)
    {
	    if (const auto it = m_MusicList.find(id); it == m_MusicList.end())
        {
            return;
        }

        if(m_CurrentlyPlayingMusic != m_MusicList[id])
        {
            Mix_VolumeMusic(static_cast<int>(volume));
            Mix_PlayMusic(m_MusicList[id], numberOfLoops);
            m_CurrentlyPlayingMusic = m_MusicList[id];
        }
        else
        {
            ResumeMusic();
        }
    }

    static void PauseMusic()
    {
        Mix_PauseMusic();
    }

    static void ResumeMusic()
    {
        if (Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
    }

    void StopMusic()
    {
        Mix_HaltMusic();
        m_CurrentlyPlayingMusic = nullptr;
    }
    

private:
    Mix_Music* m_CurrentlyPlayingMusic = nullptr;

    std::jthread m_SoundThread;

    std::queue<SoundDataStruct> m_EventQueue;

	std::map<int, Mix_Chunk*> m_SoundEffectList;

    std::map<int, Mix_Music*> m_MusicList;

    std::mutex m_Mutex;

    std::condition_variable m_ConditionVariable;

    void LoadInSoundEffect(const int id, const std::string& filePath)
    {
        Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());

        m_SoundEffectList[id] = soundEffect;
    }

    void LoadInMusic(const int id, const std::string& filePath)
    {
        Mix_Music* music = Mix_LoadMUS(filePath.c_str());

        m_MusicList[id] = music;
    }

    void InfiniteLoop()
    {
        std::unique_lock<std::mutex> lock(m_Mutex);

        do
        {
            m_ConditionVariable.wait(lock, [&]
            {
	            return (!m_EventQueue.empty());
            });

            const auto& [quit,music, volume, loops] = m_EventQueue.front();
            m_EventQueue.pop();

            if(quit)
            {
                return;
            }
            Mix_VolumeChunk(music, static_cast<int>(volume));
            Mix_PlayChannel(-1,music, loops);
        }
        while (true);
    }
};
#pragma endregion


#pragma region SdlSoundSystem

dae::SdlSoundSystem::~SdlSoundSystem()
{
    delete m_Pimpl;
}

void dae::SdlSoundSystem::PlaySoundEffect(const sound_id id, const float volume, const int numberOfLoops)
{
    m_Pimpl->PlaySoundEffect(id, volume, numberOfLoops);
}

void dae::SdlSoundSystem::PlayMusic(const sound_id id, const float volume, const int numberOfLoops)
{
    m_Pimpl->PlayMusic(id, volume, numberOfLoops);
}

void dae::SdlSoundSystem::PauseMusic()
{
	dae::SdlSoundSystem::MixerImpl::PauseMusic();
}

void dae::SdlSoundSystem::ResumeMusic()
{
	dae::SdlSoundSystem::MixerImpl::ResumeMusic();
}

void dae::SdlSoundSystem::StopMusic()
{
    m_Pimpl->StopMusic();
}

void dae::SdlSoundSystem::Initialize(const std::string dataPath, const std::map<int, std::string> soundEffectList, const std::map<int, std::string> musicList)
{
    m_Pimpl = new MixerImpl();
    m_Pimpl->Initialize(dataPath, soundEffectList,musicList);
}

#pragma endregion