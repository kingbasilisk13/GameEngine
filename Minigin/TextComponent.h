#pragma once
#include "BaseComponent.h"

#include <string>

namespace dae
{
	class Font;
	class RenderComponent;
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
		void FixedUpdate() override;
		void Render() const override;

		void ChangeText(const std::string& text);
		void ChangeFont(const std::shared_ptr<Font>& font);

	private:
		bool m_TextureIsDirty;
		std::shared_ptr<Font> m_Font;
		std::string m_Text;
		RenderComponent* m_RenderComponent;

		void GetRenderComponent();

		void GenerateTexture();

		void ReloadPointers() override;
	};
}