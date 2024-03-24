#pragma once
#include "Singleton.h"

#include "Minigin.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
		//only minigin is allowed to change the value of m_DeltaTime.
		friend void Minigin::Run(const std::function<void()>& load) const;

	public:
		float GetDeltaTime() const { return m_DeltaTime; }

		float GetFixedTimeStep() const { return m_FixedTimeStep; }
	private:
		void ChangeDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }

		void SetFixedTimeStep(float fixedTimeStep) { m_FixedTimeStep = fixedTimeStep; }

		float m_DeltaTime{ 0.0f };

		float m_FixedTimeStep{0.0f};
	};
}


