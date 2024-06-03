#pragma once
#include <glm/vec2.hpp>

#include "IState.h"

//todo: remove enum and just use vector. also just change value in class itself, dont make new object of class.
//todo: remove magic numbers.

class PatrollingState final : public dae::IState
{
public:
	PatrollingState();

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

	const float m_Speed = 10.f;

	glm::vec2 m_Direction = {1,0};

	float m_TimePassed = 0.f;

	void Move(dae::GameObject* owner);

	bool HitWall(dae::GameObject* owner) const;

	glm::vec2 m_FuturePosition;

};

