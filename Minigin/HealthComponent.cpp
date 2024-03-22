#include "HealthComponent.h"
#include <iostream>

dae::HealthComponent::HealthComponent(GameObject* gameObject, const float maxHealth, const float currentHealth)
:BaseComponent(gameObject)
,m_MaxHealth(maxHealth)
,m_CurrentHealth(currentHealth)
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
