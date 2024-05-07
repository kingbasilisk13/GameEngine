#include "RenderComponent.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject, Texture2D* texture)
	:BaseComponent(gameObject)
	, m_Texture(texture)
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::FixedUpdate()
{
}


//todo: instead of puttings this render code in the render loop move it to a public function that other components can call in their render loop.

void dae::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto position = GetOwningGameObject()->GetWorldPosition();

		Renderer::GetInstance().RenderTexture(m_Texture->GetSdlTexture(), position.x, position.y);
	}
}

void dae::RenderComponent::ChangeTexture(Texture2D* texture)
{
	m_Texture = texture;
}