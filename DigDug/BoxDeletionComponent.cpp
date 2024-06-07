#include "BoxDeletionComponent.h"

#include "BoxComponent.h"
#include "Rectf.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

BoxDeletionComponent::BoxDeletionComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{
}

void BoxDeletionComponent::Update()
{
	//todo: warning this will cause errors if the scene does not contain a player 1 object.
	auto player1 = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByName("player1");

	if(player1 == nullptr)
	{
		return;
	}

	dae::Rectf thisObject = GetOwningGameObject()->GetComponent<dae::BoxComponent>()->GetBox();


	if (player1->HasComponent<dae::BoxComponent>())
	{
		dae::Rectf otherObject = player1->GetComponent<dae::BoxComponent>()->GetBox();

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

void BoxDeletionComponent::FixedUpdate()
{
}

void BoxDeletionComponent::Render() const
{
}
