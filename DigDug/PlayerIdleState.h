#pragma once
#include "IPlayerStateBase.h"

namespace dae
{
	enum class FlipImage;
}

class PlayerIdleState final : public IPlayerStateBase
{
public:
	explicit PlayerIdleState(PlayerInput previousDirection, dae::FlipImage imageFlip);
	~PlayerIdleState() override = default;

	void HandleInput(PlayerInput input) override;

	IState* Update(dae::GameObject* owner) override;

	void OnEnter(dae::GameObject* owner) override;

	void OnExit() override;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) = delete;

private:
	bool m_PressedInput = false;

	PlayerInput m_PreviousDirection;
	dae::FlipImage m_Flip;
};
