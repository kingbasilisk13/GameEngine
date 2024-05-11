#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject, Texture2D* texture)
	: BaseComponent(gameObject)
	, m_SizeToContent(true)
	, m_ZOrder(0)
	, m_DestinationWidth(0)
	, m_DestinationHeight(0)
	, m_SourcePositionX(0)
	, m_SourcePositionY(0)
	, m_SourceWidth(0)
	, m_SourceHeight(0)
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

		if(m_SizeToContent)
		{
			Renderer::GetInstance().RenderTexture(
				m_ZOrder, 
				m_Texture, 
				static_cast<int>(position.x), 
				static_cast<int>(position.y)
			);
		}
		else
		{
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
}

void dae::RenderComponent::ChangeTexture(Texture2D* texture)
{
	m_Texture = texture;
}

void dae::RenderComponent::SizeToContent(const bool sizeToContent)
{
	m_SizeToContent = sizeToContent;
}

void dae::RenderComponent::SetZOrder(const int zOrder)
{
	m_ZOrder = zOrder;
}

void dae::RenderComponent::SetSourceValues(const int x, const int y, const int width, const int height)
{
	m_SourcePositionX = x;
	m_SourcePositionY = y;
	m_SourceWidth = width;
	m_SourceHeight = height;
}

void dae::RenderComponent::SetDestinationSize(const int width, const int height)
{
	m_DestinationWidth = width;
	m_DestinationHeight = height;
}
