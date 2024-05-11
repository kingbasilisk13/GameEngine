#include "BoxComponent.h"


dae::BoxComponent::BoxComponent(GameObject* gameObject,const float width,const float height)
	:BaseComponent(gameObject)
{
	const glm::vec2 center = gameObject->GetWorldPosition();
	m_Box = ReCalculateBox(center, width, height);
}

void dae::BoxComponent::Update()
{
	if(GetOwningGameObject()->IsPositionDirty())
	{
		const glm::vec2 center = GetOwningGameObject()->GetWorldPosition();
		m_Box = ReCalculateBox(center, m_Box.width, m_Box.height);
	}
}

void dae::BoxComponent::FixedUpdate()
{
}

void dae::BoxComponent::Render() const
{
}

void dae::BoxComponent::ChangeDimensions(const float width, const float height)
{
	const glm::vec2 center = GetOwningGameObject()->GetWorldPosition();
	m_Box = ReCalculateBox(center, width, height);
}

dae::Rectf dae::BoxComponent::GetBox() const
{
	return m_Box;
}

dae::Rectf dae::BoxComponent::GetFutureBox(glm::vec2 center) const
{
	return ReCalculateBox(center, m_Box.width, m_Box.height);
}

dae::Rectf dae::BoxComponent::ReCalculateBox(const glm::vec2 center, const float width, const float height)
{
	dae::Rectf result{};
	result.width = width;
	result.height = height;

	result.left = center.x;
	result.top = center.y;

	return result;
}