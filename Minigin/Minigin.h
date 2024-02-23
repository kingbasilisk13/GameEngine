#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		//todo: figure out how to set the fixed time step. does it need to be during construction?
		explicit Minigin(const std::string& dataPath, int frameRate = 60, float fixedTimeStep = 0.02f);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		//equal to 0.02 seconds.
		int m_FrameRate{ 60 };
		float m_FixedTimeStep{ 0.02f };
	};
}