#include "PlayerIdleState.h"

#include "AnimationComponent.h"
#include "GameObject.h"
#include "PlayerWalkingState.h"

PlayerIdleState::PlayerIdleState(const PlayerInput previousDirection, dae::FlipImage imageFlip)
	:m_PreviousDirection(previousDirection)
	,m_Flip(imageFlip)
{
}

void PlayerIdleState::HandleInput(PlayerInput )
{
	m_PressedInput = true;
}

dae::IState* PlayerIdleState::Update(dae::GameObject* )
{
	if(m_PressedInput)
	{
		return new PlayerWalkingState(m_PreviousDirection,m_Flip);
	}

	return nullptr;
}

void PlayerIdleState::OnEnter(dae::GameObject* owner)
{
	m_PressedInput = false;
	owner->GetComponent<dae::AnimationComponent>()->PauseAnimation(true);
}

void PlayerIdleState::OnExit()
{
	m_PressedInput = false;
}
