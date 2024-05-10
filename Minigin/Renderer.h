#pragma once
#include <map>
#include <SDL.h>
#include "Singleton.h"

namespace dae
{
	class Texture2D;

	struct RenderInfo
	{
		int zOrder = 0;
		Texture2D* textureToRender;
		SDL_Rect sourceRect;
		SDL_Rect destinationRect;

		RenderInfo(int zorder, Texture2D* texture, SDL_Rect src, SDL_Rect dest)
		{
			zOrder = zorder;
			textureToRender = texture;
			sourceRect = src;
			destinationRect = dest;
		}
	};

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

		void RenderTexture(int zOrder, Texture2D* texture, int x, int y);
		void RenderTexture(int zOrder, Texture2D* texture, int x, int y, int width, int height);


		//used for animations
		void RenderTexture(
			int zOrder,
			Texture2D* texture,
			int destinationX, 
			int destinationY, 
			int destinationWidth, 
			int destinationHeight, 
			int sourceX, 
			int sourceY,
			int sourceWidth,
			int sourceHeight);

		[[nodiscard]] SDL_Renderer* GetSDLRenderer() const;

		[[nodiscard]] const SDL_Color& GetBackgroundColor() const { return m_clearColor; }

		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void DisplayRenderMap();

	private:
		

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};

		std::multimap<int, RenderInfo> m_RenderMap;

		MemoryTestImGui* m_ImGuiObject{};

		
	};
}

