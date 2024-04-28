#include "HealthComponent.h"


HealthComponent::HealthComponent(dae::GameObject* gameObject, const int numberOfLives)
:BaseComponent(gameObject)
,m_Lives(numberOfLives)
{
	m_HealthChangedEvent = std::make_unique<dae::Subject>(this);
}

void HealthComponent::Update()
{
}

void HealthComponent::FixedUpdate()
{
}

void HealthComponent::Render() const
{
}

void HealthComponent::Kill()
{
	m_Lives -= 1;
	m_HealthChangedEvent->Notify(dae::Event::ActorDied);
}

int HealthComponent::GetRemainingLives() const
{
	return m_Lives;
}

void HealthComponent::SubscribeToHealthChangedEvent(dae::IObserver* observer) const
{
	m_HealthChangedEvent->AddObserver(observer);
}
