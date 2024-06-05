#pragma once
#include "IPlayerStateBase.h"


class PlayerAttackingState final : public IPlayerStateBase
{
public:

	PlayerAttackingState() = default;
	~PlayerAttackingState() override = default;

	void HandleInput(PlayerInput input) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;

	PlayerAttackingState(const PlayerAttackingState& other) = delete;
	PlayerAttackingState(PlayerAttackingState&& other) = delete;
	PlayerAttackingState& operator=(const PlayerAttackingState& other) = delete;
	PlayerAttackingState& operator=(PlayerAttackingState&& other) = delete;

private:
	
};
