#include <stdexcept>
#include "Renderer.h"

#include <ranges>

#include "imgui.h"
#include "SceneManager.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "MemoryTestImGui.h"
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

//draw a texture at a certain location with the dimensions of the image.
void dae::Renderer::RenderTexture(const int zOrder, Texture2D* texture, const int x, const int y)
{
	const glm::ivec2 dimensions = texture->GetSize();

	RenderTexture(
		zOrder, 
		texture,
		x,
		y,
		dimensions.x,
		dimensions.y,
		0,
		0,
		dimensions.x,
		dimensions.y
	);

}

//draw a texture at a certain location with self chosen dimensions.
void dae::Renderer::RenderTexture(const int zOrder, Texture2D* texture, const int x, const int y, const int width, const int height)
{
	const glm::ivec2 dimensions = texture->GetSize();

	RenderTexture(
		zOrder,
		texture,
		x,
		y,
		width,
		height,
		0,
		0,
		dimensions.x,
		dimensions.y
	);
}


void dae::Renderer::RenderTexture(
	int zOrder,
	Texture2D* texture,
	int destinationX, 
	int destinationY, 
	int destinationWidth, 
	int destinationHeight, 
	int sourceX, 
	int sourceY, 
	int sourceWidth, 
	int sourceHeight)
{
	SDL_Rect dst{};
	dst.x = destinationX;
	dst.y = destinationY;
	dst.w = destinationWidth;
	dst.h = destinationHeight;

	SDL_Rect source{};
	source.x = sourceX;
	source.y = sourceY;
	source.w = sourceWidth;
	source.h = sourceHeight;


	RenderInfo info{ zOrder,texture ,source, dst };

	m_RenderMap.emplace(zOrder, info);

}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_Renderer; }

void dae::Renderer::DisplayRenderMap()
{
	for (auto& [zOrder, texture, sourceRect, destinationRect] : m_RenderMap | std::views::values)
	{
		SDL_RenderCopy(m_Renderer, texture->GetSdlTexture(), &sourceRect, &destinationRect);
	}

	m_RenderMap.clear();
}

void dae::Renderer::GetWindowSize(int* width, int* height) const
{
	SDL_GetWindowSize(m_Window,width,height);
}
