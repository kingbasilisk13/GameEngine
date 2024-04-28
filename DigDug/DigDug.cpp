#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <windows.h>

#include "ControllerInput.h"

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
#include "LoggingSoundSystem.h"
#include "SetDirectionCommand.h"
#include "MovementComponent.h"
#include "NullSoundSystem.h"
#include "PlayerObserverComponent.h"
#include "RenderComponent.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "SdlSoundSystem.h"
#include "ServiceLocator.h"
#include "Transform.h"

void InitializeGame()
{
#if _DEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SdlSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SdlSoundSystem>());
#endif


	std::map<int, std::string> audioList;


	//split up in music and sound effects.
	//audioList[1] = "01 Credit Sound.mp3";
	audioList[1] = "01 Credit Sound.wav";
	//audioList[2] = "02 Start Music.mp3";
	audioList[2] = "02 Start Music.wav";
	//audioList[3] = "03 In-Game Music.mp3";
	audioList[3] = "03 In-Game Music.wav";
	//audioList[4] = "04 Dig Dug Shot.mp3";
	//audioList[5] = "05 Dig Dug Pumping.mp3";
	audioList[5] = "05 Dig Dug Pumping.wav";
	//audioList[6] = "06 Monster Blow.mp3";
	//audioList[7] = "07 Last One Sound.mp3";
	//audioList[8] = "08 Last One Music.mp3";
	//audioList[9] = "09 Stage Clear.mp3";
	//audioList[10] = "10 Name Entry.mp3";
	//audioList[11] = "11 Monster Moving.mp3";
	//audioList[12] = "12 Fygar Flame.mp3";
	//audioList[13] = "13 Rock Dropping.mp3";
	//audioList[14] = "14 Rock Hit.mp3";
	audioList[14] = "14 Rock Hit.wav";
	//audioList[15] = "15 Rock Broken.mp3";
	audioList[15] = "15 Rock Broken.wav";
	//audioList[16] = "16 Extend Sound.mp3";
	audioList[16] = "16 Extend Sound.wav";
	//audioList[17] = "17 Bonus Sound.mp3";
	audioList[17] = "17 Bonus Sound.wav";
	//audioList[18] = "18 Hurry-Up Sound.mp3";
	//audioList[19] = "19 Hurry-Up Music.mp3";
	//audioList[20] = "20 Miss.mp3";
	//audioList[21] = "21 Game Over.mp3";
	audioList[21] = "21 Game Over.wav";
	//audioList[22] = "22 High Score.mp3";
	audioList[22] = "22 High Score.wav";

	dae::ServiceLocator::GetSoundSystem().Initialize("../Data/Sound/", audioList);

	dae::ServiceLocator::GetSoundSystem().Play(1, 5);
	dae::ServiceLocator::GetSoundSystem().Play(2, 5);
	dae::ServiceLocator::GetSoundSystem().Play(3, 5);
	dae::ServiceLocator::GetSoundSystem().Play(5, 5);



	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({0,0,0});
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.tga")));
	scene.Add(go);


	//logo
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({ 216.f, 180.f, 0.f });
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("logo.tga")));
	scene.Add(go);


	//title
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({ 80.f, 20.f, 0.f });
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get()));
	go->AddComponent(std::make_unique<dae::TextComponent>(go.get(), font, "Programming 4 Assignment"));
	scene.Add(go);


	//fps
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({});
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get()));
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(std::make_unique<dae::TextComponent>(go.get(), font));
	go->AddComponent(std::make_unique<FpsComponent>(go.get()));
	scene.Add(go);



	const float speedP1{ 100.f };
	const float speedP2{ 200.f };

	const auto player1 = std::make_shared<dae::GameObject>();
	player1->SetLocalPosition({ 216.f, 180.f, 0.f });
	player1->AddComponent(std::make_unique<dae::RenderComponent>(player1.get(), dae::ResourceManager::GetInstance().LoadTexture("Player1.png")));
	player1->AddComponent(std::make_unique<MovementComponent>(player1.get(), speedP1));
	player1->AddComponent(std::make_unique<HealthComponent>(player1.get(), 3));
	player1->AddComponent(std::make_unique<ScoreComponent>(player1.get()));
	scene.Add(player1);

	const auto component = player1->GetComponent<MovementComponent>();

	const auto healthComponentP1 = player1->GetComponent<HealthComponent>();

	const auto scoreComponentP1 = player1->GetComponent<ScoreComponent>();

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<KillCommand>(healthComponentP1),
		SDL_SCANCODE_C,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ScoreCommand>(scoreComponentP1, 100),
		SDL_SCANCODE_Z,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ScoreCommand>(scoreComponentP1, 10),
		SDL_SCANCODE_X,
		dae::KeyState::Down
	);


	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(1, 0, 0)),
		SDL_SCANCODE_D,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(-1, 0, 0)),
		SDL_SCANCODE_A,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(0, -1, 0)),
		SDL_SCANCODE_W,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(0, 1, 0)),
		SDL_SCANCODE_S,
		dae::KeyState::Pressed
	);





	const auto player2 = std::make_shared<dae::GameObject>();

	player2->SetLocalPosition({ 216.f, 180.f, 0.f });

	player2->AddComponent(std::make_unique<dae::RenderComponent>(player2.get(), dae::ResourceManager::GetInstance().LoadTexture("Player2.png")));
	player2->AddComponent(std::make_unique<MovementComponent>(player2.get(), speedP2));
	player2->AddComponent(std::make_unique<HealthComponent>(player2.get(), 3));
	player2->AddComponent(std::make_unique<ScoreComponent>(player2.get()));
	scene.Add(player2);

	const auto temp = player2->GetComponent<MovementComponent>();

	const auto healthComponentP2 = player2->GetComponent<HealthComponent>();

	const auto scoreComponentP2 = player2->GetComponent<ScoreComponent>();

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<KillCommand>(healthComponentP2),
		0,
		dae::ControllerInput::Gamepad_X,
		dae::KeyState::Down
		
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ScoreCommand>(scoreComponentP2, 100),
		0,
		dae::ControllerInput::Gamepad_A,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ScoreCommand>(scoreComponentP2, 10),
		0,
		dae::ControllerInput::Gamepad_B,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(temp, glm::vec3(1, 0, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Right,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(temp, glm::vec3(-1, 0, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Left,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(temp, glm::vec3(0, -1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Up,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(temp, glm::vec3(0, 1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Down,
		dae::KeyState::Pressed
	);


	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//health display 1
	const auto player1HealthObserver = std::make_shared<dae::GameObject>();

	player1HealthObserver->SetLocalPosition({ 0.f, 140.f, 0.f });

	player1HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1HealthObserver.get()));
	player1HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player1HealthObserver.get(), font, "# lives: 3"));
	player1HealthObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player1HealthObserver.get()));
	scene.Add(player1HealthObserver);

	player1->GetComponent<HealthComponent>()->SubscribeToHealthChangedEvent(player1HealthObserver->GetComponent<PlayerObserverComponent>());


	//score display 1
	const auto player1ScoreObserver = std::make_shared<dae::GameObject>();

	player1ScoreObserver->SetLocalPosition({ 0.f, 160.f, 0.f });

	player1ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1ScoreObserver.get()));
	player1ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player1ScoreObserver.get(), font, "Score: 0"));
	player1ScoreObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player1ScoreObserver.get()));
	scene.Add(player1ScoreObserver);

	player1->GetComponent<ScoreComponent>()->SubscribeToScoreChangedEvent(player1ScoreObserver->GetComponent<PlayerObserverComponent>());




	//health display 2
	const auto player2HealthObserver = std::make_shared<dae::GameObject>();

	player2HealthObserver->SetLocalPosition({ 0.f, 180.f, 0.f });

	player2HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2HealthObserver.get()));
	player2HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player2HealthObserver.get(), font, "# lives: 3"));
	player2HealthObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player2HealthObserver.get()));
	scene.Add(player2HealthObserver);

	player2->GetComponent<HealthComponent>()->SubscribeToHealthChangedEvent(player2HealthObserver->GetComponent<PlayerObserverComponent>());

	//score display 2
	const auto player2ScoreObserver = std::make_shared<dae::GameObject>();

	player2ScoreObserver->SetLocalPosition({ 0.f, 200.f, 0.f });

	player2ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2ScoreObserver.get()));
	player2ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player2ScoreObserver.get(), font, "Score: 0"));
	player2ScoreObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player2ScoreObserver.get()));
	scene.Add(player2ScoreObserver);

	player2->GetComponent<ScoreComponent>()->SubscribeToScoreChangedEvent(player2ScoreObserver->GetComponent<PlayerObserverComponent>());

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//controls display
	const auto controlsDisplay1 = std::make_shared<dae::GameObject>();

	controlsDisplay1->SetLocalPosition({ 0.f, 60.f, 0.f });

	controlsDisplay1->AddComponent(std::make_unique<dae::RenderComponent>(controlsDisplay1.get()));
	controlsDisplay1->AddComponent(std::make_unique<dae::TextComponent>(controlsDisplay1.get(), font,
	                                                                    "Using the D-Pad to move the yellow sprite, X to inflict damage, A and B To increase their score."));
	scene.Add(controlsDisplay1);

	
	const auto controlsDisplay2 = std::make_shared<dae::GameObject>();

	controlsDisplay2->SetLocalPosition({ 0.f, 90.f, 0.f });

	controlsDisplay2->AddComponent(std::make_unique<dae::RenderComponent>(controlsDisplay2.get()));
	controlsDisplay2->AddComponent(std::make_unique<dae::TextComponent>(controlsDisplay2.get(), font,
	                                                                    "Using WASD to move the blue sprite, C to inflict damage, Z and X To increase their score."));
	scene.Add(controlsDisplay2);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(InitializeGame);
	return 0;
}