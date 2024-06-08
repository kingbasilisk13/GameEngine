#include "BoxComponent.h"

#include "Renderer.h"


dae::BoxComponent::BoxComponent(GameObject* gameObject,const float width,const float height)
	:BaseComponent(gameObject)
{
	const glm::vec2 center = gameObject->GetWorldPosition();
	m_Box = ReCalculateBox(center, width, height);
}

void dae::BoxComponent::Update()
{
	const auto owner = GetOwningGameObject();

	if(owner->IsPositionDirty())
	{
		const glm::vec2 center = owner->GetWorldPosition();
		m_Box = ReCalculateBox(center, m_Box.width, m_Box.height);
	}
}

void dae::BoxComponent::FixedUpdate()
{
}

void dae::BoxComponent::Render() const
{
	Renderer::GetInstance().RenderRectanle(m_Box);
}

void dae::BoxComponent::ChangeDimensions(const float width, const float height)
{
	const glm::vec2 center = GetOwningGameObject()->GetWorldPosition();
	m_Box = ReCalculateBox(center, width, height);
}

dae::Rectf dae::BoxComponent::GetBox()
{
	const glm::vec2 center = GetOwningGameObject()->GetWorldPosition();
	m_Box = ReCalculateBox(center, m_Box.width, m_Box.height);
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


	//re calculate the position so it is the actual top left corner and not the center.
	result.left = center.x - (width / 2);
	result.top = center.y - (height / 2);

	return result;
}