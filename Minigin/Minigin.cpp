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
#include "EngineTime.h"
#include <chrono>
#include <thread>
#include "EventManager.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "NullSoundSystem.h"
#include "ServiceLocator.h"

SDL_Window* g_window{};

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_SoundSystemInstance{ std::make_unique<dae::NullSoundSystem>() };

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

dae::Minigin::Minigin(const std::string &dataPath, const int width, const int height, const int frameRate, const float fixedTimeStep):
	m_FixedTimeStep( fixedTimeStep )
{
	m_FrameRate = static_cast<int>((1.f / abs(frameRate)) * 1000);

	PrintSdlVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"2DAE18_Eeckhout_Michiel_exam_DigDug",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
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
	const auto& input = InputManager::GetInstance();

	load();

	const auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = EngineTime::GetInstance();

	bool doContinue{ true };
	
	auto lastTime{ std::chrono::high_resolution_clock::now() };
	
	float lag{ 0.0f };

	time.SetFixedTimeStep(m_FixedTimeStep);

	

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();

		time.ChangeDeltaTime(std::chrono::duration<float>(currentTime - lastTime).count());

		lastTime = currentTime;
		lag += time.GetDeltaTime();

		doContinue = input.ProcessInput();

		while (lag >= m_FixedTimeStep)
		{
			//todo: nog steeds opzoek naar een use case voor dit.
			//sceneManager.FixedUpdate();
			lag -= m_FixedTimeStep;
		}
		sceneManager.Update();

		//wat is late update? just a second update. But it is not just calling the update a second time. it is a special update just be specific objects, like the camera.
		//updates of any kind always happen before the render.

		renderer.Render();

		const auto sleepTime = currentTime + std::chrono::milliseconds(m_FrameRate) - std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(sleepTime);
	}
}
