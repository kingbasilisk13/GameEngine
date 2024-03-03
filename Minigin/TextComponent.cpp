#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "RenderComponent.h"


dae::TextComponent::TextComponent(GameObject* gameObject, std::shared_ptr<Font> font, std::string text)
	:BaseComponent(gameObject)
	, m_Font(std::move(font))
	, m_Text(std::move(text))
	, m_RenderComponent(nullptr)
{
	GetRenderComponent();
	GenerateTexture();
}

void dae::TextComponent::Update()
{
	if (m_RenderComponent == nullptr)
	{
		GetRenderComponent();
		if (m_RenderComponent == nullptr)
		{
			return;
		}
	}
}

void dae::TextComponent::FixedUpdate(float)
{
}

void dae::TextComponent::Render(float , float ) const
{
}

void dae::TextComponent::ChangeText(const std::string& text)
{
	m_Text = text;
	GenerateTexture();
}

void dae::TextComponent::ChangeFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
	GenerateTexture();
}

void dae::TextComponent::GetRenderComponent()
{
	m_RenderComponent = GetOwningGameObject()->GetComponent<RenderComponent>();
}

void dae::TextComponent::GenerateTexture() const
{
	constexpr SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	const auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	if(m_RenderComponent != nullptr)
	{
		m_RenderComponent->ChangeTexture(std::make_shared<Texture2D>(texture));
	}
}
