#pragma once
#include <map>
#include <SDL.h>
#include "RenderComponent.h"
#include "Singleton.h"

namespace dae
{
	struct Rectf;
	class Texture2D;

	class MemoryTestImGui;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(RenderInfo renderInfo);

		void RenderRectanle(Rectf box);

		[[nodiscard]] SDL_Renderer* GetSDLRenderer() const;

		[[nodiscard]] const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }

		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

		void DisplayRenderMap();

		void GetWindowSize(int* width, int* height) const;

	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_ClearColor{};

		std::multimap<int, RenderInfo> m_RenderMap;

		std::vector<SDL_Rect> m_DebugRectanlges;

		MemoryTestImGui* m_ImGuiObject{};
	};
}

