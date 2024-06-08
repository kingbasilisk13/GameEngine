#include "PlayerIdleState.h"

#include "AnimationComponent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "PlayerDyingState.h"
#include "PlayerWalkingState.h"

PlayerIdleState::PlayerIdleState(const PlayerInput previousDirection, dae::FlipImage imageFlip)
	:m_PreviousDirection(previousDirection)
	,m_Flip(imageFlip)
{
	
}

PlayerIdleState::~PlayerIdleState()
{
	dae::EventManager::GetInstance().UnSubscribe(this);
}

void PlayerIdleState::HandleInput(PlayerInput )
{
	m_PressedInput = true;
}

dae::IState* PlayerIdleState::Update(dae::GameObject* )
{
	if(m_PlayerHasDied)
	{
		return new PlayerDyingState();
	}

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
	dae::EventManager::GetInstance().Subscribe(this);
}

void PlayerIdleState::OnExit()
{
	dae::EventManager::GetInstance().UnSubscribe(this);
	m_PressedInput = false;
}

void PlayerIdleState::OnGlobalNotify(const std::string event)
{
	if (event == "Player1GotHit")
	{
		m_PlayerHasDied = true;
	}
}

void PlayerIdleState::OnNotify(dae::Subject* , dae::Event )
{
}

void PlayerIdleState::AddSubject(dae::Subject* )
{
}

void PlayerIdleState::InformAllSubjects(std::vector<dae::Subject*> )
{
}
