#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"


dae::TextComponent::TextComponent(GameObject* gameObject, const std::string& text, std::shared_ptr<Font> font) :
	BaseComponent(gameObject),
	m_NeedsUpdate(true), 
	m_Text(text), 
	m_Font(std::move(font)), 
	m_Texture(nullptr)
{
	GenerateTexture();
}

dae::TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		GenerateTexture();
	}
}

void dae::TextComponent::FixedUpdate(float fixedTimeStep)
{
	fixedTimeStep;
}

void dae::TextComponent::Render(float posX, float posY) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(m_Texture, posX, posY);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::GenerateTexture()
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_Texture = texture;
	m_NeedsUpdate = false;
}
