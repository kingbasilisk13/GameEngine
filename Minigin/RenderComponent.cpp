#include <SDL.h>
#include <utility>
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture)
	:BaseComponent(gameObject)
	, m_Texture(std::move(texture))
	, m_Owner(nullptr)
{
	m_Owner = GetOwningGameObject();
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::FixedUpdate(float)
{
}

void dae::RenderComponent::Render(float, float) const
{
	//todo: ask if it is a good idea to request to current location every render.
	// maybe find a way to only ask for the current location when it changes. maybe in the update loop.
	if (m_Texture != nullptr)
	{
		const auto position = m_Owner->GetWorldPosition();

		Renderer::GetInstance().RenderTexture(m_Texture->GetSDLTexture(), position.x, position.y);
	}
}

void dae::RenderComponent::ChangeTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = std::move(texture);
}