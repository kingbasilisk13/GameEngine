#pragma once
#include "BaseComponent.h"


//a component that moves the game object in a grid like pattern. requires the setting of direction each frame to move.
class GridMovementComponent final : public dae::BaseComponent
{
public:
	explicit GridMovementComponent(dae::GameObject* gameObject, float movementSpeed);

	~GridMovementComponent() override = default;
	GridMovementComponent(const GridMovementComponent& other) = delete;
	GridMovementComponent(GridMovementComponent&& other) = delete;
	GridMovementComponent& operator=(const GridMovementComponent& other) = delete;
	GridMovementComponent& operator=(GridMovementComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetMovementSpeed(const float movementSpeed);

	void SetMovementDirection(const glm::vec2 direction);

	void SetBounds(glm::vec2 topLeft, glm::vec2 bottomRight);

	void SetGridValues(const std::vector<int>& xValues, const std::vector<int>& yValues);

private:
	float m_MovementSpeed{};

	glm::vec2 m_Direction{};
	glm::vec2 m_LastDirection{};

	int m_WindowWidth;
	int m_WindowHeight;

	bool m_UseCustomBound = false;

	glm::vec2 m_TopLeftBoundPosition{};
	glm::vec2 m_BottomRightBoundPosition{};

	static bool CheckPassingOverBounds(glm::vec2 newPosition, glm::vec2 topLeft, glm::vec2 bottomRight);

	std::vector<int> m_XValues;
	std::vector<int> m_YValues;


	bool PerformProhibitedMovement(glm::vec2 newPosition) const;

};
