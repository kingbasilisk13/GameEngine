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

dae::PlayerObserverComponent::~PlayerObserverComponent()
{
	InformAllSubjects(m_Subjects);
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

//diferent notifies dictaded how the score changes.
//kill monster = +10
//gather point = +100
void dae::PlayerObserverComponent::OnNotify(Subject* subject, const Event event)
{
	switch (event) {
	case Event::ActorDied:
		m_TextComponent->ChangeText(std::format("# lives: {}", dynamic_cast<HealthComponent*>(subject->GetOwner())->GetRemainingLives()));
		break;
	case Event::ScoreIncreased:
		m_TextComponent->ChangeText(std::format("Score: {}", dynamic_cast<ScoreComponent*>(subject->GetOwner())->GetScore()));
		break;
	case Event::SubjectIsDeleted:
		std::erase_if(m_Subjects, [&](const Subject* ptr)
			{
				if (ptr == subject)
				{
					return true;
				}
				return false;
			});
	}
}

void dae::PlayerObserverComponent::AddSubject(Subject* subject)
{
	m_Subjects.push_back(subject);
}

void dae::PlayerObserverComponent::InformAllSubjects(std::vector<Subject*> subjects)
{
	for (const auto subject : m_Subjects)
	{
		subject->RemoveObserver(this);
	}
}

void dae::PlayerObserverComponent::ReloadPointers()
{
	m_TextComponent = GetOwningGameObject()->GetComponent<TextComponent>();
	m_ComponentsAreDirty = false;
}
