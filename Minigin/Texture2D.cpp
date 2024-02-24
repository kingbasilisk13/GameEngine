#include <SDL.h>
#include "Texture2D.h"

#include "ResourceManager.h"
#include <string>

#include "Renderer.h"

dae::Texture2D::Texture2D(const std::string& fileName):
	dae::BaseComponent()
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

dae::Texture2D::Texture2D(SDL_Texture* texture):
	m_Texture(texture)
{
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

void dae::Texture2D::Update()
{
}

//todo: add code to render texture here.
void dae::Texture2D::Render(float posX, float posY) const
{
	Renderer::GetInstance().RenderTexture(m_Texture, posX, posY);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}


