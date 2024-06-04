#pragma once
#include <glm/vec2.hpp>

#include "IState.h"

class FygarWanderState final : public dae::IState
{
public:
	FygarWanderState();

	~FygarWanderState() override;

	IState* HandleInput(dae::GameObject* owner) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;
	void OnExit() override;


	FygarWanderState(const FygarWanderState& other) = delete;
	FygarWanderState(FygarWanderState&& other) = delete;
	FygarWanderState& operator=(const FygarWanderState& other) = delete;
	FygarWanderState& operator=(FygarWanderState&& other) = delete;

private:
	const int m_MinWanderTime = 10;
	const int m_MaxWanderTime = 20;

	float m_WanderTime;

	const float m_Speed = 40.f;

	glm::vec2 m_Direction = { 1,0 };

	float m_TimePassed = 0.f;

	void Move(dae::GameObject* owner);

	bool HitWall(dae::GameObject* owner) const;

	glm::vec2 m_FuturePosition;

};
