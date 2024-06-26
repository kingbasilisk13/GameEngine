#pragma once
#include <glm/vec2.hpp>

#include "IState.h"

//todo: remove enum and just use vector. also just change value in class itself, dont make new object of class.
//todo: remove magic numbers.

class PookaWanderState final : public dae::IState
{
public:
	PookaWanderState();

	~PookaWanderState() override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;
	void OnExit() override;


	PookaWanderState(const PookaWanderState& other) = delete;
	PookaWanderState(PookaWanderState&& other) = delete;

	PookaWanderState& operator=(const PookaWanderState& other) = delete;
	PookaWanderState& operator=(PookaWanderState&& other) = delete;

private:
	const int m_MinWanderTime = 10;
	const int m_MaxWanderTime = 20;
	float m_WanderTime;

	const float m_Speed = 55.f;

	glm::vec2 m_Direction = {1,0};

	float m_TimePassed = 0.f;

	void Move(dae::GameObject* owner);

	bool HitWall(dae::GameObject* owner) const;

	glm::vec2 m_FuturePosition;

};

