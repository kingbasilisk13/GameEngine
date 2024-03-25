#include <utility>
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture)
	:BaseComponent(gameObject)
	, m_Texture(std::move(texture))
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

		Renderer::GetInstance().RenderTexture(m_Texture->GetSdlTexture(), position.x, position.y);
	}
}

void dae::RenderComponent::ChangeTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = std::move(texture);
}