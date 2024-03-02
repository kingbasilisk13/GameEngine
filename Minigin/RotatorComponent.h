#pragma once
#include "BaseComponent.h"

namespace dae
{
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

		float m_MaxTime{3.f};

		glm::vec3 m_Center;

		GameObject& m_Owner;

		float m_Pi2;

		void CalculateRotation(float time);

	};
}