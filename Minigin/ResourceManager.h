#pragma once
#include <memory>
#include <string>
#include "Texture2D.h"
#include "Font.h"
#include <unordered_map>

#include "Singleton.h"

//todo: herschrijv deze manager zo dat wanneer een nieuw font of texture wordt ingeladen het in de map wordt gezet.

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);

		Texture2D* LoadTexture(const std::string& file);

		Font* LoadFont(const std::string& file, unsigned int size);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::string m_dataPath;

		std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_MapOfTextures;

		std::unordered_map<std::string, std::unique_ptr<Font>> m_MapOfFonts;

	};
}
