#include "BoxDeletionComponent.h"

#include "BoxComponent.h"
#include "GameModeSelectorComponent.h"
#include "Rectf.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

BoxDeletionComponent::BoxDeletionComponent(dae::GameObject* gameObject, const GameMode gameMode)
	: BaseComponent(gameObject)
	, m_GameMode(gameMode)
{
}

void BoxDeletionComponent::Update()
{
	//todo: warning this will cause errors if the scene does not contain a player 1 object.
	if(m_Player1 == nullptr)
	{
		m_Player1 = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByName("player1").get();
	}

	if(m_Player1 != nullptr)
	{
		CheckIfNeedToDeleteCell(m_Player1);
	}

	switch (m_GameMode)
	{
	case GameMode::coOp:
		if (m_Player2 == nullptr)
		{
			m_Player2 = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByName("player2").get();
		}

		if (m_Player2 != nullptr)
		{
			CheckIfNeedToDeleteCell(m_Player2);
		}
		break;
	default: ;
	}

	
}

void BoxDeletionComponent::FixedUpdate()
{
}

void BoxDeletionComponent::Render() const
{
}

void BoxDeletionComponent::CheckIfNeedToDeleteCell(dae::GameObject* player)
{
	if (player == nullptr)
	{
		return;
	}

	dae::Rectf thisObject = GetOwningGameObject()->GetComponent<dae::BoxComponent>()->GetBox();


	if (player->HasComponent<dae::BoxComponent>())
	{
		dae::Rectf otherObject = player->GetComponent<dae::BoxComponent>()->GetBox();

		if (dae::utils::IsOverlapping(thisObject, otherObject))
		{
			auto owner = GetOwningGameObject();

			auto size = dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png")->GetSize();

			auto renderer = owner->GetComponent<dae::RenderComponent>();
			renderer->ChangeSourceValues(0, 0, size.x, size.y);

			owner->RemoveComponent(owner->GetComponent<dae::BoxComponent>());
			owner->RemoveComponent(this);
		}
	}
}
