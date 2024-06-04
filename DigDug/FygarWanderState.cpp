#include "FygarWanderState.h"

#include "BoxComponent.h"
#include "EngineTime.h"
#include "FygarGhostState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "utils.h"


FygarWanderState::FygarWanderState(): m_FuturePosition()
{
	m_WanderTime = static_cast<float>(rand() % (m_MaxWanderTime - m_MinWanderTime + 1) + m_MinWanderTime);
}
;

FygarWanderState::~FygarWanderState() = default;

dae::IState* FygarWanderState::HandleInput(dae::GameObject*)
{
	return nullptr;
}

dae::IState* FygarWanderState::Update(dae::GameObject* owner)
{
	Move(owner);

	if (HitWall(owner))
	{
		m_FuturePosition = owner->GetWorldPosition();
		//todo: this will cause problems because now there is 1 whole frame where the enemy does nothing.
		if (m_Direction == glm::vec2{ 0,-1 })
		{
			m_Direction = glm::vec2{ 1,0 };
		}
		else if (m_Direction == glm::vec2{ 1,0 })
		{
			m_Direction = glm::vec2{ 0,1 };
		}
		else if (m_Direction == glm::vec2{ 0,1 })
		{
			m_Direction = glm::vec2{ -1,0 };
		}
		else if (m_Direction == glm::vec2{ -1,0 })
		{
			m_Direction = glm::vec2{ 0,-1 };
		}
	}


	const float time = dae::EngineTime::GetInstance().GetDeltaTime();
	m_TimePassed += time;

	if(m_TimePassed >= m_WanderTime)
	{
		return new FygarGhostState();
	}

	owner->SetLocalPosition(m_FuturePosition);

	return nullptr;
}

void FygarWanderState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Fygar/Default.png"));

}

void FygarWanderState::OnExit()
{
}

void FygarWanderState::Move(dae::GameObject* owner)
{
	m_FuturePosition = owner->GetWorldPosition() + (m_Direction * m_Speed * dae::EngineTime::GetInstance().GetDeltaTime());
}

bool FygarWanderState::HitWall(dae::GameObject* owner) const
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	const dae::Rectf thisObject = owner->GetComponent<dae::BoxComponent>()->GetFutureBox(m_FuturePosition);

	for (auto& object : objects)
	{
		if (object.get() != owner && object->HasComponent<dae::BoxComponent>())
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