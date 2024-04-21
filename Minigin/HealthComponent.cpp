#include "HealthComponent.h"


dae::HealthComponent::HealthComponent(GameObject* gameObject, const int numberOfLives)
:BaseComponent(gameObject)
,m_Lives(numberOfLives)
{
	m_HealthChangedEvent = std::make_unique<dae::Subject>(this);
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
	m_HealthChangedEvent->Notify(Event::ActorDied);
}

int dae::HealthComponent::GetRemainingLives() const
{
	return m_Lives;
}

void dae::HealthComponent::SubscribeToHealthChangedEvent(IObserver* observer) const
{
	m_HealthChangedEvent->AddObserver(observer);
}
