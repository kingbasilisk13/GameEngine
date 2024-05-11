#pragma once
#include <glm/glm.hpp>

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
	glm::vec2 m_Target;

	const float m_TimeDelay = 5.f;

	float m_PassedTime = 0.f;

	void FindTarget();

	void Move(dae::GameObject* owner);

	bool IsOverlappingWall(dae::GameObject* owner) const;
};

