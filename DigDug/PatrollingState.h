#pragma once
#include "IState.h"

class PatrollingState final : public dae::IState
{
public:
	PatrollingState() = default;

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

	float m_TimePassed = 0.f;

};

