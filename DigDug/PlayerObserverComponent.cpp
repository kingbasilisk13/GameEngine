#include "PlayerObserverComponent.h"

#include "TextComponent.h"
#include <format>

#include "HealthComponent.h"
#include "ScoreComponent.h"

PlayerObserverComponent::PlayerObserverComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_TextComponent(nullptr)
{
}

PlayerObserverComponent::~PlayerObserverComponent()
{
	InformAllSubjects(m_Subjects);
}

void PlayerObserverComponent::Update()
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

void PlayerObserverComponent::FixedUpdate()
{
}

void PlayerObserverComponent::Render() const
{
}

//diferent notifies dictaded how the score changes.
//kill monster = +10
//gather point = +100
void PlayerObserverComponent::OnNotify(dae::Subject* subject, const dae::Event event)
{
	switch (event) {
	case dae::Event::ActorDied:
		m_TextComponent->ChangeText(std::format("# lives: {}", dynamic_cast<HealthComponent*>(subject->GetOwner())->GetRemainingLives()));
		break;
	case dae::Event::ScoreIncreased:
		m_TextComponent->ChangeText(std::format("Score: {}", dynamic_cast<ScoreComponent*>(subject->GetOwner())->GetScore()));
		break;
	case dae::Event::SubjectIsDeleted:
		std::erase_if(m_Subjects, [&](const dae::Subject* ptr)
			{
				if (ptr == subject)
				{
					return true;
				}
				return false;
			});
	}
}

void PlayerObserverComponent::AddSubject(dae::Subject* subject)
{
	m_Subjects.push_back(subject);
}

void PlayerObserverComponent::InformAllSubjects(std::vector<dae::Subject*> subjects)
{
	for (const auto subject : m_Subjects)
	{
		subject->RemoveObserver(this);
	}
}

void PlayerObserverComponent::ReloadPointers()
{
	m_TextComponent = GetOwningGameObject()->GetComponent<dae::TextComponent>();
	m_ComponentsAreDirty = false;
}
