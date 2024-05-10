#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* gameObject, Font* font, std::string text)
	:BaseComponent(gameObject)
	, m_TextureIsDirty(false)
	, m_Font(font)
	, m_Text(std::move(text))
	, m_RenderComponent(nullptr)
{
	GetRenderComponent();
	GenerateTexture();
}

void dae::TextComponent::Update()
{
	if (m_ComponentsAreDirty)
	{
		ReloadPointers();
	}

	if (m_RenderComponent == nullptr)
	{
		return;
	}


	if(m_TextureIsDirty)
	{
		GenerateTexture();
	}
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::ChangeText(const std::string& text)
{
	m_Text = text;
	m_TextureIsDirty = true;
}

void dae::TextComponent::GetRenderComponent()
{
	m_RenderComponent = GetOwningGameObject()->GetComponent<RenderComponent>();
}

void dae::TextComponent::ChangeFont(Font* font)
{
	m_Font = font;
	m_TextureIsDirty = true;
}

void dae::TextComponent::GenerateTexture()
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

	if (m_RenderComponent != nullptr)
	{
		m_Texture = std::make_unique<Texture2D>(texture);
		m_RenderComponent->ChangeTexture(m_Texture.get());
	}

	m_TextureIsDirty = false;
}

void dae::TextComponent::ReloadPointers()
{
	m_RenderComponent = GetOwningGameObject()->GetComponent<RenderComponent>();
	m_ComponentsAreDirty = false;
}
