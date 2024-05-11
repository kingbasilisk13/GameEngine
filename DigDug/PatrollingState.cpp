#include "PatrollingState.h"

#include "BoxComponent.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "GhostState.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"


PatrollingState::PatrollingState(const Direction direction, const float timePassed)
	: m_Direction(direction)
	, m_TimePassed(timePassed)
	, m_FuturePosition()
{
}

PatrollingState::~PatrollingState()
{
}

dae::IState* PatrollingState::HandleInput(dae::GameObject* )
{
	return nullptr;
}

dae::IState* PatrollingState::Update(dae::GameObject* owner)
{
	Move(owner);

	if(HitWall(owner))
	{
		//todo: this will cause problems because now there is 1 whole frame where the enemy does nothing.
		switch (m_Direction)
		{
		case Direction::up:
			return new PatrollingState(Direction::right,m_TimePassed);
			break;
		case Direction::right:
			return new PatrollingState(Direction::down, m_TimePassed);
			break;
		case Direction::down:
			return new PatrollingState(Direction::left, m_TimePassed);
			break;
		case Direction::left:
			return new PatrollingState(Direction::up, m_TimePassed);
			break;
		}
	}


	const float time = dae::EngineTime::GetInstance().GetDeltaTime();
	m_TimePassed += time;

	if(m_TimePassed >= m_WanderTime)
	{
		return new GhostState();
	}

	owner->SetLocalPosition(m_FuturePosition);

	return nullptr;
}

void PatrollingState::OnEnter(dae::GameObject* owner)
{
	owner->GetComponent<dae::RenderComponent>()->ChangeTexture(dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png"));
}

void PatrollingState::OnExit()
{
}

void PatrollingState::Move(dae::GameObject* owner)
{
	const float time = dae::EngineTime::GetInstance().GetDeltaTime();

	const float speed = 10.f * time;

	auto position = owner->GetWorldPosition();

	glm::vec2 directionVector = {0,0};
	switch (m_Direction)
	{
	case Direction::up:
		directionVector = {0,-1};
		break;
	case Direction::right:
		directionVector = { 1,0 };
		break;
	case Direction::down:
		directionVector = { 0,1 };
		break;
	case Direction::left:
		directionVector = { -1,0 };
		break;
	}

	position.x += directionVector.x * speed;
	position.y += directionVector.y * speed;

	//todo: this can be solved using double buffer, but right now I do not know hot to implement it.
	m_FuturePosition = position;

	
}

bool PatrollingState::HitWall(dae::GameObject* owner) const
{
	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectsInScene();

	const dae::Rectf thisObject = owner->GetComponent<dae::BoxComponent>()->GetFutureBox(m_FuturePosition);

	for(auto& object : objects)
	{
		if(object.get() != owner && object->HasComponent<dae::BoxComponent>())
		{
			dae::Rectf otherObject = object->GetComponent<dae::BoxComponent>()->GetBox();

			if(dae::utils::IsOverlapping(thisObject,otherObject))
			{
				return true;
			}
		}
	}
	return false;
}
