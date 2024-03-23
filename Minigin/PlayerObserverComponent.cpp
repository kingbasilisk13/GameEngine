#include "PlayerObserverComponent.h"

#include "TextComponent.h"
#include <format>

#include "HealthComponent.h"
#include "ScoreComponent.h"

dae::PlayerObserverComponent::PlayerObserverComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_TextComponent(nullptr)
{
}

void dae::PlayerObserverComponent::Update()
{
	if (m_ComponentsAreDirty)
	{
		ReloadPointers();
	}
	if (m_TextComponent == nullptr)
	{
		return;
	}
}

void dae::PlayerObserverComponent::FixedUpdate()
{
}

void dae::PlayerObserverComponent::Render() const
{
}

void dae::PlayerObserverComponent::OnNotify(BaseComponent* component, const Event event)
{
	switch (event) {
	case Event::ActorDied:
		m_TextComponent->ChangeText(std::format("# lives: {}", dynamic_cast<HealthComponent*>(component)->GetRemainingLives()));
		break;
	case Event::ScoreIncreased:
		m_TextComponent->ChangeText(std::format("Score: {}", dynamic_cast<ScoreComponent*>(component)->GetScore()));
		break;
	}
}

void dae::PlayerObserverComponent::ReloadPointers()
{
	m_TextComponent = GetOwningGameObject()->GetComponent<TextComponent>();
	m_ComponentsAreDirty = false;
}
