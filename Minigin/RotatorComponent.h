#pragma once
#include <SDL_stdinc.h>

#include "BaseComponent.h"

namespace dae
{
	//changes the local position is a circular pattern.
	class RotatorComponent final : public BaseComponent
	{
	public:
		explicit RotatorComponent(GameObject* gameObject, float radius, float maxTime, bool clockwise = false);

		~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

	private:
		bool m_Clockwise;

		float m_Radius;

		float m_TotalTime;

		float m_MaxTime;

		GameObject* m_Owner;

		const float m_Pi2{ 2.f * static_cast<float>(M_PI) };

		void CalculateRotation(float time);

	};
}