#include "BoxComponent.h"


dae::BoxComponent::BoxComponent(GameObject* gameObject,const float width,const float height)
	:BaseComponent(gameObject)
{
	ReCalculateBox(width, height);
}

void dae::BoxComponent::Update()
{
}

void dae::BoxComponent::FixedUpdate()
{
}

void dae::BoxComponent::Render() const
{
}

void dae::BoxComponent::ChangeDimensions(const float width, const float height)
{
	ReCalculateBox(width,height);
}

dae::Rectf dae::BoxComponent::GetBox() const
{
	return m_Box;
}

void dae::BoxComponent::ReCalculateBox(const float width,const float height)
{
	m_Box.width = width;
	m_Box.height = height;

	const glm::vec3 center = GetOwningGameObject()->GetWorldPosition();

	m_Box.left = center.x - (width * 0.5f);
	m_Box.bottom = center.y + (height * 0.5f);
}
