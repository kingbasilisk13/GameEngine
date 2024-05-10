#include "PatrollingState.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "GhostState.h"
#include "RenderComponent.h"
#include "ResourceManager.h"


PatrollingState::~PatrollingState()
{
}

dae::IState* PatrollingState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* PatrollingState::Update(dae::GameObject* owner)
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = 10.f * time;

	auto position = owner->GetWorldPosition();

	position.x += speed;

	owner->SetLocalPosition(position);

	m_TimePassed += time;

	if(m_TimePassed >= m_WanderTime)
	{
		return new GhostState();
	}

	return nullptr;
}

void PatrollingState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png"));
}

void PatrollingState::OnExit()
{
}
