#include <stdexcept>
#include "Renderer.h"
#include "imgui.h"
#include "SceneManager.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "MemoryTestImGui.h"

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
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
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
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);
	SceneManager::GetInstance().Render();

	SDL_RenderFlush(m_renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	//m_ImGuiObject->DrawImGuiWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//delete m_ImGuiObject;

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

//draw a texture at a certain location with the dimensions of the image.
void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

//draw a texture at a certain location with self chosen dimensions.
void dae::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}


void dae::Renderer::RenderTexture(
	SDL_Texture* texture, 
	float destinationX, 
	float destinationY, 
	float destinationWidth, 
	float destinationHeight, 
	float sourceX, 
	float sourceY, 
	float sourceWidth, 
	float sourceHeight) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(destinationX);
	dst.y = static_cast<int>(destinationY);
	dst.w = static_cast<int>(destinationWidth);
	dst.h = static_cast<int>(destinationHeight);

	SDL_Rect source{};
	dst.x = static_cast<int>(sourceX);
	dst.y = static_cast<int>(sourceY);
	dst.w = static_cast<int>(sourceWidth);
	dst.h = static_cast<int>(sourceHeight);
	SDL_RenderCopy(GetSDLRenderer(), texture, &source, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }