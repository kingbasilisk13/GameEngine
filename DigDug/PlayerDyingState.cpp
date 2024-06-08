#include "PlayerDyingState.h"

#include "AnimationComponent.h"
#include "EventManager.h"
#include "PlayerIdleState.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

void PlayerDyingState::HandleInput(PlayerInput)
{
}

dae::IState* PlayerDyingState::Update(dae::GameObject* )
{

	const float time = dae::EngineTime::GetInstance().GetDeltaTime();
	m_TimePassed += time;

	if (m_TimePassed >= m_DeathAnimationTime)
	{
		return new PlayerIdleState(PlayerInput::right, dae::FlipImage::None);
	}

	return nullptr;
}

void PlayerDyingState::OnEnter(dae::GameObject* owner)
{
	m_AnimationComponent = owner->GetComponent<dae::AnimationComponent>();
	m_AnimationComponent->PauseAnimation(false);
	m_AnimationComponent->ChangeNumberOfColumns(4);
	m_AnimationComponent->ChangeTimeBetweenFrames(0.5f);
	m_AnimationComponent->SetPlayAnimationOnce(true);


	m_RenderComponent = owner->GetComponent<dae::RenderComponent>();
	m_RenderComponent->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Death.png"));


}

void PlayerDyingState::OnExit()
{
	m_AnimationComponent->PauseAnimation(true);
	m_AnimationComponent->ChangeNumberOfColumns(2);
	m_AnimationComponent->ChangeTimeBetweenFrames(0.5f);
	m_AnimationComponent->SetPlayAnimationOnce(false);


	m_RenderComponent->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png"));
	dae::EventManager::GetInstance().BroadcastEvent("ResetLevel");
}
