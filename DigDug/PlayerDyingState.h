#pragma once
#include "IPlayerStateBase.h"


class PlayerDyingState final :public IPlayerStateBase
{
public:

	PlayerDyingState() = default;
	~PlayerDyingState() override = default;

	void HandleInput(PlayerInput input) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;

	PlayerDyingState(const PlayerDyingState& other) = delete;
	PlayerDyingState(PlayerDyingState&& other) = delete;
	PlayerDyingState& operator=(const PlayerDyingState& other) = delete;
	PlayerDyingState& operator=(PlayerDyingState&& other) = delete;

private:

};
