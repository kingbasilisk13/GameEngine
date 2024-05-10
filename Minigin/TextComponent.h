#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Renderer;
	class Font;
	class RenderComponent;
	class TextComponent final : public BaseComponent
	{
	public:
		explicit TextComponent(GameObject* gameObject, Font* font, std::string text = " ");

		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void ChangeText(const std::string& text);
		void ChangeFont(Font* font);

	private:
		bool m_TextureIsDirty;

		Font* m_Font;

		std::string m_Text;

		RenderComponent* m_RenderComponent;

		std::unique_ptr<Texture2D> m_Texture;

		void GetRenderComponent();

		void GenerateTexture();

		void ReloadPointers() override;
	};
}