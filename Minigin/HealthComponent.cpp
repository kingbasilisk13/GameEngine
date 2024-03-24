#include "HealthComponent.h"


dae::HealthComponent::HealthComponent(GameObject* gameObject, const int numberOfLives)
:BaseComponent(gameObject)
,m_Lives(numberOfLives)
{
}

void dae::HealthComponent::Update()
{
}

void dae::HealthComponent::FixedUpdate()
{
}

void dae::HealthComponent::Render() const
{
}

void dae::HealthComponent::Kill()
{
	m_Lives -= 1;
	Notify(this, Event::ActorDied);
}

int dae::HealthComponent::GetRemainingLives() const
{
	return m_Lives;
}
