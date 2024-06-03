#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(
	GameObject* gameObject, 
	int zOrder,
	int destinationWidth,
	int destinationHeight,
	int sourceX,
	int sourceY,
	int sourceWidth,
	int sourceHeight,
	Texture2D* texture)
	: BaseComponent(gameObject)
	, m_ZOrder(zOrder)
	, m_DestinationWidth(destinationWidth)
	, m_DestinationHeight(destinationHeight)
	, m_SourcePositionX(sourceX)
	, m_SourcePositionY(sourceY)
	, m_SourceWidth(sourceWidth)
	, m_SourceHeight(sourceHeight)
	, m_Texture(texture)
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::FixedUpdate()
{
}

void dae::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto position = GetOwningGameObject()->GetWorldPosition();

		Renderer::GetInstance().RenderTexture(
			m_ZOrder,
			m_Texture,
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			m_DestinationWidth,
			m_DestinationHeight,
			m_SourcePositionX,
			m_SourcePositionY,
			m_SourceWidth,
			m_SourceHeight
		);
	}
}

void dae::RenderComponent::ChangeTexture(Texture2D* texture)
{
	m_Texture = texture;
}

void dae::RenderComponent::ChangeZOrder(const int zOrder)
{
	m_ZOrder = zOrder;
}

void dae::RenderComponent::ChangeSourceValues(const int x, const int y, const int width, const int height)
{
	m_SourcePositionX = x;
	m_SourcePositionY = y;
	m_SourceWidth = width;
	m_SourceHeight = height;
}

void dae::RenderComponent::ChangeDestinationSize(const int width, const int height)
{
	m_DestinationWidth = width;
	m_DestinationHeight = height;
}
