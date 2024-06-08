#include "ResetPositionComponent.h"

#include "EventManager.h"

ResetPositionComponent::ResetPositionComponent(dae::GameObject* gameObject, glm::vec2 resetPosition)
	:BaseComponent(gameObject)
,m_ResetPosition(resetPosition)
{
	dae::EventManager::GetInstance().Subscribe(this);
}

ResetPositionComponent::~ResetPositionComponent()
{
	dae::EventManager::GetInstance().UnSubscribe(this);
}

void ResetPositionComponent::Update()
{
}

void ResetPositionComponent::FixedUpdate()
{
}

void ResetPositionComponent::Render() const
{
}

void ResetPositionComponent::OnGlobalNotify(const std::string event)
{
	if (event == "ResetLevel")
	{
		ResetPosition();
	}
}

void ResetPositionComponent::OnNotify(dae::Subject* , dae::Event )
{
}

void ResetPositionComponent::AddSubject(dae::Subject* )
{
}

void ResetPositionComponent::InformAllSubjects(std::vector<dae::Subject*> )
{
}

void ResetPositionComponent::ResetPosition() const
{
	GetOwningGameObject()->SetLocalPosition(m_ResetPosition);
}
