#pragma once
#include "BaseComponent.h"

namespace dae
{
	//a test component dat will remove a component after a given time
	class TimerComponent final : public BaseComponent
	{
	public:
		explicit TimerComponent(GameObject* gameObject);

		~TimerComponent() override = default;
		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
	private:
		bool m_TaskFinished{ false };

		float m_ElapsedTime{ 0.f };
	};
}
