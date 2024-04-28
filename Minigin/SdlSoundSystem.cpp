#include "SdlSoundSystem.h"
#include <iostream>
#include <mutex>
#include <queue>
#include <ranges>
#include <thread>

#include "SDL_mixer.h"


struct SoundDataStruct
{
    Mix_Chunk* music;
	float volume;
    bool quit = false;
};


#pragma region PIMPL
class dae::SdlSoundSystem::MixerImpl
{
public:
    MixerImpl() = default;

    ~MixerImpl()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);

        m_EventQueue.push(
            {

                nullptr,
                0,
                true
            });

        m_ConditionVariable.notify_all();


        for (const auto& snd : m_AudioList | std::views::values)
        {
            //Mix_FreeMusic(snd);
            Mix_FreeChunk(snd);
        }
        Mix_CloseAudio();
    }

    MixerImpl(const MixerImpl& other) = delete;
    MixerImpl(MixerImpl&& other) = delete;
    MixerImpl& operator=(const MixerImpl& other) = delete;
    MixerImpl& operator=(MixerImpl&& other) = delete;

    //pushes sound event to queue
    void Play(const sound_id id, const float volume)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);

        m_EventQueue.push(
            {
                m_AudioList[id],
                volume
            });

        m_ConditionVariable.notify_one();
    }

    void Initialize(const std::string& dataPath, const std::map<int, std::string>& audioList)
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cout << "ERROR: unable to initialize SDL_mixer";
            return;
        }

        for (const auto& [fst, snd] : audioList)
        {
            LoadInMusic(fst, dataPath + snd);
        }

        m_SoundThread = std::jthread(&MixerImpl::InfiniteLoop, this);
    }

private:
    std::jthread m_SoundThread;

    std::queue<SoundDataStruct> m_EventQueue;

	std::map<int, Mix_Chunk*> m_AudioList;

    std::mutex m_Mutex;

    std::condition_variable m_ConditionVariable;


    void LoadInMusic(const int id, const std::string& filePath)
    {
        Mix_Chunk* music = Mix_LoadWAV(filePath.c_str());

        m_AudioList[id] = music;
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

            const auto& [music, volume, quit] = m_EventQueue.front();
            m_EventQueue.pop();

            if(quit)
            {
                return;
            }
            else
            {
                Mix_PlayChannel(-1,music, -1);
            }
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

void dae::SdlSoundSystem::Play(const sound_id id, const float volume)
{
    m_Pimpl->Play(id, volume);
}

void dae::SdlSoundSystem::Initialize(const std::string dataPath, const std::map<int, std::string> audioList)
{
    m_Pimpl = new MixerImpl();
    m_Pimpl->Initialize(dataPath, audioList);
}

#pragma endregion