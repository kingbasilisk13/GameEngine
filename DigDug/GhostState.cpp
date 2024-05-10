#include "GhostState.h"

#include "PatrollingState.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::IState* GhostState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* GhostState::Update(dae::GameObject* owner)
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = 10.f * time;

	auto position = owner->GetWorldPosition();

	position.x -= speed;

	owner->SetLocalPosition(position);

	m_TimePassed += time;

	if (m_TimePassed >= m_WanderTime)
	{
		return new PatrollingState();
	}

	return nullptr;
}

void GhostState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Pooka/Ghost.png"));
}

void GhostState::OnExit()
{
}
