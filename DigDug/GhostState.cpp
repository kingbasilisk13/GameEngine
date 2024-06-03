#include "GhostState.h"

#include "BoxComponent.h"
#include "PatrollingState.h"
#include "Rectf.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

dae::IState* GhostState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* GhostState::Update(dae::GameObject* owner)
{
	FindTarget();

	Move(owner);

	if(m_PassedTime < m_TimeDelay)
	{
		const float time = dae::EngineTime::GetInstance().GetDeltaTime();
		m_PassedTime += time;
	}
	else
	{
		if (!IsOverlappingWall(owner))
		{
			glm::vec2 direction = m_Target - owner->GetWorldPosition();

			//todo: calculate optimal direction to reach player.


			return new PatrollingState();
		}
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

void GhostState::FindTarget()
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	for(const auto& object : objects)
	{
		if(object->GetObjectName() == "player1")
		{
			m_Target = object->GetWorldPosition();
			return;
		}
	}
}

void GhostState::Move(dae::GameObject* owner)
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = 10.f * time;

	auto position = owner->GetWorldPosition();

	const glm::vec2 direction = m_Target - position;

	position += normalize(direction) * speed;

	owner->SetLocalPosition(position);
}

bool GhostState::IsOverlappingWall(dae::GameObject* owner) const
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	const dae::Rectf thisObject = owner->GetComponent<dae::BoxComponent>()->GetBox();

	for (auto& object : objects)
	{
		if (object->GetObjectName() == "tile" && object->HasComponent<dae::BoxComponent>())
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
