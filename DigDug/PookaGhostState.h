#pragma once
#include <glm/glm.hpp>

#include "IState.h"

class PookaGhostState final : public dae::IState
{
public:

	PookaGhostState() = default;
	~PookaGhostState() override = default;

	IState* HandleInput(dae::GameObject* owner) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;


	PookaGhostState(const PookaGhostState& other) = delete;
	PookaGhostState(PookaGhostState&& other) = delete;
	PookaGhostState& operator=(const PookaGhostState& other) = delete;
	PookaGhostState& operator=(PookaGhostState&& other) = delete;

private:
	glm::vec2 m_Target;

	const float m_TimeDelay = 5.f;
	const float m_Speed = 30.f;

	float m_PassedTime = 0.f;

	void FindTarget();

	void Move(dae::GameObject* owner) const;

	static bool IsOverlappingWall(dae::GameObject* owner);
};

