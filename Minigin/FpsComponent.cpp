#include "FpsComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"

dae::FpsComponent::FpsComponent(GameObject* gameObject, std::shared_ptr<Font> font):
	BaseComponent(gameObject),
	m_Font(std::move(font)),
	m_Texture(nullptr),
	m_FrameCount(0),
	m_ElapsedTime(0.0f)
{
	GenerateTexture(" ");
}

dae::FpsComponent::~FpsComponent()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::FpsComponent::Update()
{
	// Calculate the time elapsed since the last frame
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedSeconds = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();

	// Update the last frame time
	m_LastFrameTime = currentTime;

	// Increment frame count and add elapsed time
	m_FrameCount++;
	m_ElapsedTime += elapsedSeconds;

	// If one second has elapsed, calculate and display FPS
	if (m_ElapsedTime >= 1.0f) {
		float fps = static_cast<float>(m_FrameCount) / m_ElapsedTime;

		std::string text = std::to_string(fps) + " FPS";
		GenerateTexture(text);

		// Reset frame count and elapsed time for the next second
		m_FrameCount = 0;
		m_ElapsedTime = 0.0f;
	}
}

void dae::FpsComponent::FixedUpdate(float fixedTimeStep)
{
	fixedTimeStep;
}

void dae::FpsComponent::Render(float posX, float posY) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(m_Texture, posX, posY);
	}
}

void dae::FpsComponent::GenerateTexture(const std::string& text)
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), color);
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
}
