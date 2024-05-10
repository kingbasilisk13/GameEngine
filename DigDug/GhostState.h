#pragma once
#include "IState.h"

class GhostState final : public dae::IState
{
public:

	GhostState() = default;
	~GhostState() override = default;

	IState* HandleInput(dae::GameObject* owner) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;


	GhostState(const GhostState& other) = delete;
	GhostState(GhostState&& other) = delete;
	GhostState& operator=(const GhostState& other) = delete;
	GhostState& operator=(GhostState&& other) = delete;

private:
	const float m_WanderTime = 10.f;

	float m_TimePassed = 0.f;
};

