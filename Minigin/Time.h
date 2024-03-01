#pragma once
#include "Singleton.h"

#include "Minigin.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
		//only minigin is allowed to change the value of m_DeltaTime.
		friend void dae::Minigin::Run(const std::function<void()>& load) const;

	public:
		float GetDeltaTime() const { return m_DeltaTime; }

	private:
		void ChangeDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }

		float m_DeltaTime{ 0.0f };
	};
}


