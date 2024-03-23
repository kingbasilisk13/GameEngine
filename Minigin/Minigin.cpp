#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "Time.h"

#include <chrono>
#include <steam_api_common.h>
#include <thread>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

SDL_Window* g_window{};

void PrintSdlVersion()
{
	SDL_version version{};
	SDL_VERSION(&version)
	printf("We compiled against SDL version %u.%u.%u ...\n",
	       version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version)
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
	       version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath, int frameRate, float fixedTimeStep):
	m_FixedTimeStep( fixedTimeStep )
{
	m_FrameRate = static_cast<int>((1.f / abs(frameRate)) * 1000);

	PrintSdlVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load) const
{
	auto& input = InputManager::GetInstance();
	input.Initialize();

	load();

	const auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = Time::GetInstance();

	bool doContinue{ true };
	
	auto lastTime{ std::chrono::high_resolution_clock::now() };
	
	float lag{ 0.0f };

	//tip: when debugging code it can be handy to clamp delta time so that when the code continues that delta time won't be too large.
	// if (delta time > 1) delta time = 0.01f;

	time.SetFixedTimeStep(m_FixedTimeStep);

	

	while (doContinue)
	{
		SteamAPI_RunCallbacks();

		const auto currentTime = std::chrono::high_resolution_clock::now();

		//this code is meant for debugging. This enshures that stepping through the code does not cause to large of a time gap.
		/*float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		if (deltaTime > 1) deltaTime = 0.01f;
		time.ChangeDeltaTime(deltaTime);*/

		//comment this code when using the debugging code.
		time.ChangeDeltaTime(std::chrono::duration<float>(currentTime - lastTime).count());

		lastTime = currentTime;
		lag += time.GetDeltaTime();

		doContinue = input.ProcessInput();

		while (lag >= m_FixedTimeStep)
		{
			sceneManager.FixedUpdate();
			lag -= m_FixedTimeStep;
		}
		sceneManager.Update();
		//wat is late update? just a second update. But it is not just calling the update a second time. it is a special update just be specific objects, like the camera.
		//updates of any kind always happen before the render.
		renderer.Render();

		const auto sleepTime = currentTime + std::chrono::milliseconds(m_FrameRate) - std::chrono::high_resolution_clock::now();

		//todo: look into using vsync instead of sleep
		std::this_thread::sleep_for(sleepTime);
	}
}
