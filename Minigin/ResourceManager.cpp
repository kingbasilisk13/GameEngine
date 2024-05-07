#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"

//todo: remove forward decleration in preference of including in header. als je circulaire dependencies krijggt wijst dit op slegte code en moet je beginnen met abstrageren.


void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	if (m_MapOfTextures.contains(file))
	{
		return m_MapOfTextures[file].get();
	}

	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_MapOfTextures[file] = std::make_unique<Texture2D>(texture);

	return m_MapOfTextures[file].get();
}

//reason why there is a unique pointer for each font size is because how the font class is makes.
//font class keeps pointer to font, font is created using file path and font.
//to change the font is to change the pointer. result. text that changes will have the font of the last item that changed the font
dae::Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	std::string key = file + std::to_string(size);

	if(m_MapOfFonts.contains(key))
	{
		return m_MapOfFonts[key].get();
	}

	m_MapOfFonts[key] = std::make_unique<Font>(m_dataPath + file, size);

	return m_MapOfFonts[key].get();
}
