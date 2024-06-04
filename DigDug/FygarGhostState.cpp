#include "FygarGhostState.h"

#include "BoxComponent.h"
#include "EngineTime.h"
#include "FygarWanderState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "utils.h"

dae::IState* FygarGhostState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* FygarGhostState::Update(dae::GameObject* owner)
{
	FindTarget();

	Move(owner);

	if (m_PassedTime < m_TimeDelay)
	{
		const float time = dae::EngineTime::GetInstance().GetDeltaTime();
		m_PassedTime += time;
	}
	else
	{
		if (!IsOverlappingWall(owner))
		{
			return new FygarWanderState();
		}
	}

	return nullptr;
}

void FygarGhostState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Fygar/Ghost.png"));

}

void FygarGhostState::OnExit()
{
}

void FygarGhostState::FindTarget()
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	for (const auto& object : objects)
	{
		if (object->GetObjectName() == "player1")
		{
			m_Target = object->GetWorldPosition();
			return;
		}
	}
}

void FygarGhostState::Move(dae::GameObject* owner) const
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = m_Speed * time;

	auto position = owner->GetWorldPosition();

	const glm::vec2 direction = m_Target - position;

	position += normalize(direction) * speed;

	owner->SetLocalPosition(position);
}

bool FygarGhostState::IsOverlappingWall(dae::GameObject* owner)
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	const dae::Rectf thisObject = owner->GetComponent<dae::BoxComponent>()->GetBox();

	for (auto& object : objects)
	{
		if (object->GetObjectName() == "tunnel" && object->HasComponent<dae::BoxComponent>())
		{
			dae::Rectf otherObject = object->GetComponent<dae::BoxComponent>()->GetBox();

			if (dae::utils::IsOverlapping(thisObject, otherObject))
			{
				return true;
			}
		}
	}
	return false;
}
