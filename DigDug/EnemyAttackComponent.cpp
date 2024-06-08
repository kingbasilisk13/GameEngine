#include "EnemyAttackComponent.h"

#include "BoxComponent.h"
#include "EventManager.h"
#include "Rectf.h"
#include "Scene.h"
#include "SceneManager.h"

EnemyAttackComponent::EnemyAttackComponent(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
	
}

void EnemyAttackComponent::Update()
{
	dae::Rectf playerBox = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByName("player1")->GetComponent<dae::BoxComponent>()->GetBox();

	dae::Rectf enemyBox = GetOwningGameObject()->GetComponent<dae::BoxComponent>()->GetBox();

	if (dae::utils::IsOverlapping(playerBox, enemyBox))
	{
		dae::EventManager::GetInstance().BroadcastEvent("Player1GotHit");
	}
}

void EnemyAttackComponent::FixedUpdate()
{
}

void EnemyAttackComponent::Render() const
{
}
