#pragma once
#include "BaseComponent.h"



class MovementComponent final : public dae::BaseComponent
{
public:
	explicit MovementComponent(dae::GameObject* gameObject, float movementSpeed);

	~MovementComponent() override = default;
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetMovementSpeed(const float movementSpeed);

	void AddToMovementDirection(const glm::vec3 direction);

private:
	float m_MovementSpeed{};

	glm::vec3 m_Direction{};

};
