#pragma once
#include "BaseComponent.h"

namespace dae
{
	//changes the local position is a circular pattern.
	class RotatorComponent final : public BaseComponent
	{
	public:
		explicit RotatorComponent(GameObject* gameObject, float radius, float speed, bool clockwise = false);

		~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

	private:
		int m_Direction{ -1 };

		float m_Radius;

		float m_Speed;

		float m_Angle{0.f};

		void CalculateRotation(float time);

	};
}