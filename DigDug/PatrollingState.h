#pragma once
#include <glm/vec2.hpp>

#include "IState.h"

enum class Direction
{
	up,
	right,
	down,
	left
};

class PatrollingState final : public dae::IState
{
public:
	PatrollingState(Direction direction, float timePassed = 0.f);

	~PatrollingState() override;

	IState* HandleInput(dae::GameObject* owner) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;
	void OnExit() override;


	PatrollingState(const PatrollingState& other) = delete;
	PatrollingState(PatrollingState&& other) = delete;

	PatrollingState& operator=(const PatrollingState& other) = delete;
	PatrollingState& operator=(PatrollingState&& other) = delete;

private:
	const float m_WanderTime = 10.f;

	Direction m_Direction;

	float m_TimePassed = 0.f;


	void Move(dae::GameObject* owner);

	bool HitWall(dae::GameObject* owner) const;

	glm::vec2 m_FuturePosition;

};

