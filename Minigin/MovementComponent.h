#pragma once
#include "BaseComponent.h"

class MovementComponent
{
};

namespace dae
{
	class MovementComponent final : public BaseComponent
	{
	public:
		explicit MovementComponent(GameObject* gameObject,const float movementSpeed = 0.f);

		~MovementComponent() override = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeMovementSpeed(const float movementSpeed);

		void AddToMovementDirection(const glm::vec3 direction);

	private:
		float m_MovementSpeed;
		glm::vec3 m_Direction{};
	};
}