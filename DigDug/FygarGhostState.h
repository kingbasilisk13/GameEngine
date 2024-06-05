#pragma once
#include <glm/vec2.hpp>

#include "IState.h"

class FygarGhostState final : public dae::IState
{
public:

	FygarGhostState() = default;
	~FygarGhostState() override = default;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;


	FygarGhostState(const FygarGhostState& other) = delete;
	FygarGhostState(FygarGhostState&& other) = delete;
	FygarGhostState& operator=(const FygarGhostState& other) = delete;
	FygarGhostState& operator=(FygarGhostState&& other) = delete;

private:
	glm::vec2 m_Target{};

	const float m_TimeDelay = 5.f;
	const float m_Speed = 30.f;

	float m_PassedTime = 0.f;

	void FindTarget();

	void Move(dae::GameObject* owner) const;

	static bool IsOverlappingWall(dae::GameObject* owner);
};
