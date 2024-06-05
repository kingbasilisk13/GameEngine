#pragma once
#include "IState.h"

enum class PlayerInput
{
	up,
	down,
	left,
	right
};

class IPlayerStateBase : public dae::IState
{
public:
	~IPlayerStateBase() override = default;

	virtual void HandleInput(PlayerInput input) = 0;

	IState* Update(dae::GameObject* owner) override = 0;

	void OnEnter(dae::GameObject* owner) override = 0;

	void OnExit() override = 0;
};
