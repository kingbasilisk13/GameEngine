#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject, RenderInfo renderInfo)
	: BaseComponent(gameObject)
	,m_RenderInfo(renderInfo)
{
	ShiftToCenter();
}

void dae::RenderComponent::Update()
{
	const auto position = GetOwningGameObject()->GetWorldPosition();
	m_RenderInfo.destinationX = static_cast<int>(position.x);
	m_RenderInfo.destinationY = static_cast<int>(position.y);
	ShiftToCenter();
}

void dae::RenderComponent::FixedUpdate()
{
}

void dae::RenderComponent::Render() const
{
	if (m_RenderInfo.textureToRender != nullptr)
	{
		

		


		//render component renders image in such a way that the center of the image alligns with the destination possition
		Renderer::GetInstance().RenderTexture(m_RenderInfo);
	}
}

void dae::RenderComponent::ChangeTexture(Texture2D* texture)
{
	m_RenderInfo.textureToRender = texture;
}

void dae::RenderComponent::ChangeZOrder(const int zOrder)
{
	m_RenderInfo.zOrder = zOrder;
}

void dae::RenderComponent::ChangeSourceValues(const int x, const int y, const int width, const int height)
{
	m_RenderInfo.sourceX = x;
	m_RenderInfo.sourceY = y;
	m_RenderInfo.sourceWidth = width;
	m_RenderInfo.sourceHeight = height;
}

void dae::RenderComponent::ChangeDestinationSize(const int width, const int height)
{
	m_RenderInfo.destinationWidth = width;
	m_RenderInfo.destinationHeight = height;
}

void dae::RenderComponent::ShiftToCenter()
{
	m_RenderInfo.destinationX = m_RenderInfo.destinationX - (m_RenderInfo.destinationWidth / 2);
	m_RenderInfo.destinationY = m_RenderInfo.destinationY - (m_RenderInfo.destinationHeight / 2);
}
