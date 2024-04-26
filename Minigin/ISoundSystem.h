#pragma once

namespace dae
{
	using sound_id = unsigned short;
	class ISoundSystem
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;


		virtual void Play(const sound_id id, const float volume) = 0;


		//other functions
		
	};
}
