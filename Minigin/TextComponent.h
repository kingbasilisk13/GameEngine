#pragma once
#include "BaseComponent.h"

#include <string>
#include <memory>
#include "Transform.h"

struct SDL_Texture;
namespace dae
{
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* gameObject, const std::string& text, std::shared_ptr<Font> font);

		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

		void SetText(const std::string& text);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Texture* m_Texture;

		void GenerateTexture();
	};
}


