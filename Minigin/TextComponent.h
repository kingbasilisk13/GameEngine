#pragma once
#include "BaseComponent.h"

#include <string>
#include <memory>

namespace dae
{
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		explicit TextComponent(GameObject* gameObject, std::shared_ptr<Font> font, std::string text = " ");

		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void FixedUpdate(float fixedTimeStep) override;
		void Render(float posX, float posY) const override;

		void ChangeText(const std::string& text);
		void ChangeFont(const std::shared_ptr<Font>& font);

	private:
		std::shared_ptr<Font> m_Font;
		std::string m_Text;

		void GenerateTexture() const;
	};
}


