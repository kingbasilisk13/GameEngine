#include <stdexcept>
#include "Renderer.h"

#include <ranges>

#include "imgui.h"
#include "SceneManager.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "MemoryTestImGui.h"
#include "RenderComponent.h"
#include "Texture2D.h"


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();

	//m_ImGuiObject = new MemoryTestImGui();
	
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderFlush(m_Renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	//m_ImGuiObject->DrawImGuiWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//delete m_ImGuiObject;

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(RenderInfo renderInfo)
{
	m_RenderMap.emplace(renderInfo.zOrder, renderInfo);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_Renderer; }

void dae::Renderer::DisplayRenderMap()
{
	for (auto& info : m_RenderMap | std::views::values)
	{
		SDL_Rect dst{};
		dst.x = info.destinationX - (info.destinationWidth/2);
		dst.y = info.destinationY - (info.destinationHeight/2);
		dst.w = info.destinationWidth;
		dst.h = info.destinationHeight;

		SDL_Rect source{};
		source.x = info.sourceX;
		source.y = info.sourceY;
		source.w = info.sourceWidth;
		source.h = info.sourceHeight;

		switch (info.imageFlip)
		{
		case FlipImage::None:
			SDL_RenderCopyEx(m_Renderer, info.textureToRender->GetSdlTexture(), &source, &dst, info.angle, NULL, SDL_FLIP_NONE);
			break;
		case FlipImage::Horizontaly:
			SDL_RenderCopyEx(m_Renderer, info.textureToRender->GetSdlTexture(), &source, &dst, info.angle, NULL, SDL_FLIP_HORIZONTAL);
			break;
		case FlipImage::Verticaly:
			SDL_RenderCopyEx(m_Renderer, info.textureToRender->GetSdlTexture(), &source, &dst, info.angle, NULL, SDL_FLIP_VERTICAL);
			break;
		}
	}
	m_RenderMap.clear();
}

void dae::Renderer::GetWindowSize(int* width, int* height) const
{
	SDL_GetWindowSize(m_Window,width,height);
}
