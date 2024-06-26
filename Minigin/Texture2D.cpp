#include <SDL.h>
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSdlTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::Texture2D::GetSdlTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
