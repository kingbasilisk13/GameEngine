#pragma once
#include "Singleton.h"

#include "Minigin.h"

namespace dae
{
	class EngineTime final : public Singleton<EngineTime>
	{
	public:
		[[nodiscard]] float GetDeltaTime() const;

		[[nodiscard]] float GetFixedTimeStep() const;

	private:
		//only minigin is allowed to change the value of m_DeltaTime.
		friend void dae::Minigin::Run(const std::function<void()>& load) const;

		friend class Singleton<EngineTime>;
		EngineTime() = default;

		void ChangeDeltaTime(const float deltaTime);

		void SetFixedTimeStep(const float fixedTimeStep);

		float m_DeltaTime{ 0.0f };

		float m_FixedTimeStep{0.0f};
	};
}


