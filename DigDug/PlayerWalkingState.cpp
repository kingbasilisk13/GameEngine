#include "PlayerWalkingState.h"

#include "AnimationComponent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "ISoundSystem.h"
#include "PlayerDyingState.h"
#include "PlayerIdleState.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"

PlayerWalkingState::PlayerWalkingState(const PlayerInput previousDirection, dae::FlipImage imageFlip)
	:m_PreviousDirection(previousDirection)
	,m_Flip(imageFlip)
{
	
}

PlayerWalkingState::~PlayerWalkingState()
{
	dae::EventManager::GetInstance().UnSubscribe(this);
}

void PlayerWalkingState::HandleInput(const PlayerInput input)
{
	switch (input)
	{
	case PlayerInput::up:
		m_Direction = PlayerInput::up;
		break;
	case PlayerInput::down:
		m_Direction = PlayerInput::down;
		break;
	case PlayerInput::left:
		m_Direction = PlayerInput::left;
		break;
	case PlayerInput::right:
		m_Direction = PlayerInput::right;
		break;
	}
	m_PlayerIsIdle = false;
}

dae::IState* PlayerWalkingState::Update(dae::GameObject* owner)
{
	if(m_PlayerHasDied)
	{
		return new PlayerDyingState();
	}
	CalculateDirection(owner);

	if(m_PlayerIsIdle)
	{
		return new PlayerIdleState(m_PreviousDirection,m_Flip);
	}

	m_PlayerIsIdle = true;
	
	return nullptr;
}

void PlayerWalkingState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::AnimationComponent>()->PauseAnimation(false);
	dae::ServiceLocator::GetSoundSystem().PlayMusic(24,50,-1);
	dae::EventManager::GetInstance().Subscribe(this);
}

void PlayerWalkingState::OnExit()
{
	dae::EventManager::GetInstance().UnSubscribe(this);
	dae::ServiceLocator::GetSoundSystem().PauseMusic();
}

void PlayerWalkingState::OnGlobalNotify(const std::string event)
{
	if(event == "Player1GotHit")
	{
		m_PlayerHasDied = true;
	}
}

void PlayerWalkingState::OnNotify(dae::Subject* , dae::Event )
{
}

void PlayerWalkingState::AddSubject(dae::Subject* )
{
}

void PlayerWalkingState::InformAllSubjects(std::vector<dae::Subject*> )
{
}

void PlayerWalkingState::CalculateDirection(dae::GameObject* owner)
{
	auto renderer = owner->GetComponent<dae::RenderComponent>();
	switch (m_Direction)
	{
	case PlayerInput::up:
		switch (m_PreviousDirection)
		{
		case PlayerInput::down:
			InvertImageFlip();
			renderer->ChangeImageFlip(m_Flip);
			break;
		case PlayerInput::left:
			renderer->ChangeAngle(90);
			break;
		case PlayerInput::right:
			renderer->ChangeAngle(-90);
			break;
		}
		break;
	case PlayerInput::down:
		switch (m_PreviousDirection)
		{
		case PlayerInput::up:
			InvertImageFlip();
			renderer->ChangeImageFlip(m_Flip);
			break;
		case PlayerInput::left:
			renderer->ChangeAngle(-90);
			break;
		case PlayerInput::right:
			renderer->ChangeAngle(90);
			renderer->ChangeImageFlip(dae::FlipImage::None);
			m_Flip = dae::FlipImage::None;
			break;
		}
		break;
	case PlayerInput::left:
		renderer->ChangeAngle(0);
		renderer->ChangeImageFlip(dae::FlipImage::Horizontaly);
		m_Flip = dae::FlipImage::Horizontaly;
		break;
	case PlayerInput::right:
		renderer->ChangeAngle(0);
		renderer->ChangeImageFlip(dae::FlipImage::None);
		m_Flip = dae::FlipImage::None;
		break;
	}

	m_PreviousDirection = m_Direction;
}

void PlayerWalkingState::InvertImageFlip()
{
	switch (m_Flip)
	{
	case dae::FlipImage::None:
		m_Flip = dae::FlipImage::Horizontaly;
		break;
	case dae::FlipImage::Horizontaly:
		m_Flip = dae::FlipImage::None;
		break;
	}
}

