#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <ostream>
#include<windows.h>
#include <Xinput.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "Scene.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "KillCommand.h"
#include "SetDirectionCommand.h"
#include "MovementComponent.h"
#include "PlayerObserverComponent.h"
#include "RenderComponent.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"

#include "Transform.h"

#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)


#include "Achievement.h"
#include "CSteamAchievements.h"
#include "SteamAchievementsObserver.h"
#include "TimerComponent.h"

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

// Achievement array which will hold data about the achievements and their state
dae::Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

// Global access to Achievements object
dae::CSteamAchievements* g_SteamAchievements = NULL;


dae::SteamAchievementsObserver* g_SteamAchievementsObserver = NULL;
//this function creates a scene and adds the components to it.
void load()
{
	//todo: labo week 5, normaal zou enkel opdracht 1 en 2 nieuwe klassen nodig hebben. als je alles goed gemaakt hebt zou opdracht 3 enkel een paar enxtra lijnen code zijn.
	//todo: steam achievement is only for lab 5. after that you delete it.

	g_SteamAchievementsObserver = new dae::SteamAchievementsObserver(g_SteamAchievements);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	dae::Transform position{};
	position.SetPosition(0.f, 0.f, 0.f);
	auto go = std::make_shared<dae::GameObject>(position);
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.tga")));
	scene.Add(go);


	//logo
	position.SetPosition(216.f, 180.f, 0.f);
	go = std::make_shared<dae::GameObject>(position);
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("logo.tga")));
	scene.Add(go);


	//title
	position.SetPosition(80.f, 20.f, 0.f);
	go = std::make_shared<dae::GameObject>(position);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get()));
	go->AddComponent(std::make_unique<dae::TextComponent>(go.get(), font, "Programming 4 Assignment" ));
	scene.Add(go);


	//fps
	position.SetPosition();
	go = std::make_shared<dae::GameObject>(position);
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get()));
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_unique<dae::TextComponent>(go.get(), font));
	go->AddComponent(std::make_unique<dae::FpsComponent>(go.get()));
	scene.Add(go);


	constexpr float speedP1{ 100.f };
	constexpr float speedP2{ 200.f };

	position.SetPosition({ 216.f, 180.f, 0.f });
	const auto player1 = std::make_shared<dae::GameObject>(position);
	player1->AddComponent(std::make_unique<dae::RenderComponent>(player1.get(), dae::ResourceManager::GetInstance().LoadTexture("Player1.png")));
	player1->AddComponent(std::make_unique<dae::MovementComponent>(player1.get(), speedP1));
	player1->AddComponent(std::make_unique<dae::HealthComponent>(player1.get(), 3));
	player1->AddComponent(std::make_unique<dae::ScoreComponent>(player1.get()));
	scene.Add(player1);

	const auto component = player1->GetComponent<dae::MovementComponent>();

	const auto healthComponentP1 = player1->GetComponent<dae::HealthComponent>();

	const auto scoreComponentP1 = player1->GetComponent<dae::ScoreComponent>();

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::KillCommand>(healthComponentP1),
		SDL_SCANCODE_C,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::ScoreCommand>(scoreComponentP1,100),
		SDL_SCANCODE_Z,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::ScoreCommand>(scoreComponentP1, 10),
		SDL_SCANCODE_X,
		dae::KeyState::Down
	);


	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::SetDirectionCommand>(component, glm::vec3(2, 0, 0)),
		SDL_SCANCODE_D,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::SetDirectionCommand>(component, glm::vec3(-1, 0, 0)),
		SDL_SCANCODE_A,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::SetDirectionCommand>(component, glm::vec3(0, -1, 0)),
		SDL_SCANCODE_W,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::SetDirectionCommand>(component, glm::vec3(0, 1, 0)),
		SDL_SCANCODE_S,
		dae::KeyState::Pressed
	);

	



	const auto player2 = std::make_shared<dae::GameObject>(position);
	player2->AddComponent(std::make_unique<dae::RenderComponent>(player2.get(), dae::ResourceManager::GetInstance().LoadTexture("Player2.png")));
	player2->AddComponent(std::make_unique<dae::MovementComponent>(player2.get(), speedP2));
	player2->AddComponent(std::make_unique<dae::HealthComponent>(player2.get(), 3));
	player2->AddComponent(std::make_unique<dae::ScoreComponent>(player2.get()));
	scene.Add(player2);

	const auto temp = player2->GetComponent<dae::MovementComponent>();

	const auto healthComponentP2 = player2->GetComponent<dae::HealthComponent>();

	const auto scoreComponentP2 = player2->GetComponent<dae::ScoreComponent>();

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::KillCommand>(healthComponentP2),
		0,
		XINPUT_GAMEPAD_X,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::ScoreCommand>(scoreComponentP2,100),
		0,
		XINPUT_GAMEPAD_A,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::ScoreCommand>(scoreComponentP2, 10),
		0,
		XINPUT_GAMEPAD_B,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::SetDirectionCommand>(temp, glm::vec3(1, 0, 0)),
		0,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::SetDirectionCommand>(temp, glm::vec3(-1, 0, 0)),
		0,
		XINPUT_GAMEPAD_DPAD_LEFT,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::SetDirectionCommand>(temp, glm::vec3(0, -1, 0)),
		0,
		XINPUT_GAMEPAD_DPAD_UP,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::SetDirectionCommand>(temp, glm::vec3(0, 1, 0)),
		0,
		XINPUT_GAMEPAD_DPAD_DOWN,
		dae::KeyState::Pressed
	);


	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//health display 1
	position.SetPosition({ 0.f, 140.f, 0.f });
	const auto player1HealthObserver = std::make_shared<dae::GameObject>(position);
	player1HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1HealthObserver.get()));
	player1HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player1HealthObserver.get(), font, "# lives: 3"));
	player1HealthObserver->AddComponent(std::make_unique<dae::PlayerObserverComponent>(player1HealthObserver.get()));
	scene.Add(player1HealthObserver);

	player1->GetComponent<dae::HealthComponent>()->AddObserver(player1HealthObserver->GetComponent<dae::PlayerObserverComponent>());
	
	//score display 1
	position.SetPosition({ 0.f, 160.f, 0.f });
	const auto player1ScoreObserver = std::make_shared<dae::GameObject>(position);
	player1ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1ScoreObserver.get()));
	player1ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player1ScoreObserver.get(), font, "Score: 0"));
	player1ScoreObserver->AddComponent(std::make_unique<dae::PlayerObserverComponent>(player1ScoreObserver.get()));
	scene.Add(player1ScoreObserver);

	player1->GetComponent<dae::ScoreComponent>()->AddObserver(player1ScoreObserver->GetComponent<dae::PlayerObserverComponent>());
	player1->GetComponent<dae::ScoreComponent>()->AddObserver(g_SteamAchievementsObserver);




	//health display 2
	position.SetPosition({ 0.f, 180.f, 0.f });
	const auto player2HealthObserver = std::make_shared<dae::GameObject>(position);
	player2HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2HealthObserver.get()));
	player2HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player2HealthObserver.get(), font, "# lives: 3"));
	player2HealthObserver->AddComponent(std::make_unique<dae::PlayerObserverComponent>(player2HealthObserver.get()));
	scene.Add(player2HealthObserver);

	player2->GetComponent<dae::HealthComponent>()->AddObserver(player2HealthObserver->GetComponent<dae::PlayerObserverComponent>());


	//score display 2
	position.SetPosition({ 0.f, 200.f, 0.f });
	const auto player2ScoreObserver = std::make_shared<dae::GameObject>(position);
	player2ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2ScoreObserver.get()));
	player2ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player2ScoreObserver.get(), font, "Score: 0"));
	player2ScoreObserver->AddComponent(std::make_unique<dae::PlayerObserverComponent>(player2ScoreObserver.get()));
	scene.Add(player2ScoreObserver);

	player2->GetComponent<dae::ScoreComponent>()->AddObserver(player2ScoreObserver->GetComponent<dae::PlayerObserverComponent>());
	player2->GetComponent<dae::ScoreComponent>()->AddObserver(g_SteamAchievementsObserver);



	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//controls display
	position.SetPosition({ 0.f, 60.f, 0.f });
	const auto controlsDisplay1 = std::make_shared<dae::GameObject>(position);
	controlsDisplay1->AddComponent(std::make_unique<dae::RenderComponent>(controlsDisplay1.get()));
	controlsDisplay1->AddComponent(std::make_unique<dae::TextComponent>(controlsDisplay1.get(), font,
		"Using the D-Pad to move the yellow sprite, X to inflict damage, A and B To increase their score."));
	scene.Add(controlsDisplay1);

	position.SetPosition({ 0.f, 90.f, 0.f });
	const auto controlsDisplay2 = std::make_shared<dae::GameObject>(position);
	controlsDisplay2->AddComponent(std::make_unique<dae::RenderComponent>(controlsDisplay2.get()));
	controlsDisplay2->AddComponent(std::make_unique<dae::TextComponent>(controlsDisplay2.get(), font,
		"Using WASD to move the blue sprite, C to inflict damage, Z and X To increase their score."));
	scene.Add(controlsDisplay2);

	
}


int main(int, char*[]) {
	if(!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
		g_SteamAchievements = new dae::CSteamAchievements(g_Achievements, 4);
	}

	//creates the minigin
	dae::Minigin engine("../Data/");
	
	//adds a reference to the function load that can then be executed in the minigin run function.
	engine.Run(load);

	SteamAPI_Shutdown();
	// Delete the SteamAchievements object
	if (g_SteamAchievements)
	{
		delete g_SteamAchievementsObserver;
		delete g_SteamAchievements;
	}

    return 0;
}