#include "PookaGhostState.h"

#include "BoxComponent.h"
#include "PookaWanderState.h"
#include "Rectf.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

dae::IState* PookaGhostState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* PookaGhostState::Update(dae::GameObject* owner)
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
			//todo: calculate optimal direction to reach player.


			return new PookaWanderState();
		}
	}

	return nullptr;
}

bool PookaGhostState::IsOverlappingWall(dae::GameObject* owner)
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

void PookaGhostState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Pooka/Ghost.png"));
}

void PookaGhostState::OnExit()
{
}

void PookaGhostState::FindTarget()
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

void PookaGhostState::Move(dae::GameObject* owner) const
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = m_Speed * time;

	auto position = owner->GetWorldPosition();

	const glm::vec2 direction = m_Target - position;

	position += normalize(direction) * speed;

	owner->SetLocalPosition(position);
}