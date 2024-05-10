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
#include "PatrollingState.h"
#include "PlayerObserverComponent.h"
#include "ReleaseButtonCommand.h"
#include "RenderComponent.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "SdlSoundSystem.h"
#include "ServiceLocator.h"
#include "StateComponent.h"
#include "Transform.h"



void InitializeGame()
{
#if _DEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SdlSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SdlSoundSystem>());
#endif

	//todo: je bent niet verplicht om dingen op specifieken manieren te doen. ze geven u de paterns, jij gebruikt ze hoe jij wilt, maar je moet kunnen uitleggen waarom.
	//todo: als je in uw if state class een in hebt die checkt voor een state gelijk aan x of niet dan kan het opgeslpits worden in 2 state classes.

	std::map<int, std::string> soundEffectList;
	std::map<int, std::string> musicList;


	//split up in music and sound effects.
	soundEffectList[1] = "01 Credit Sound.wav";
	soundEffectList[2] = "02 Start Music.wav";
	soundEffectList[4] = "04 Dig Dug Shot.wav";
	soundEffectList[5] = "05 Dig Dug Pumping.wav";
	soundEffectList[6] = "06 Monster Blow.wav";
	soundEffectList[7] = "07 Last One Sound.wav";
	soundEffectList[8] = "08 Last One Music.wav";
	soundEffectList[9] = "09 Stage Clear.wav";
	soundEffectList[10] = "10 Name Entry.wav";
	soundEffectList[11] = "11 Monster Moving.wav";
	soundEffectList[12] = "12 Fygar Flame.wav";
	soundEffectList[13] = "13 Rock Dropping.wav";
	soundEffectList[14] = "14 Rock Hit.wav";
	soundEffectList[15] = "15 Rock Broken.wav";
	soundEffectList[16] = "16 Extend Sound.wav";
	soundEffectList[17] = "17 Bonus Sound.wav";
	soundEffectList[18] = "18 Hurry-Up Sound.wav";
	soundEffectList[19] = "19 Hurry-Up Music.wav";
	soundEffectList[20] = "20 Miss.wav";
	soundEffectList[21] = "21 Game Over.wav";
	soundEffectList[22] = "22 High Score.wav";
	soundEffectList[23] = "23 PlayerDeathSound.wav";
	

	musicList[3] = "03 In-Game Music.wav";
	musicList[22] = "22 High Score.wav";
	musicList[24] = "24 PlayerWalkMusic.wav";
	

	dae::ServiceLocator::GetSoundSystem().Initialize("../Data/Sound/", soundEffectList,musicList);
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition({0,0,0});
	go->AddComponent(std::make_unique<dae::RenderComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.tga")));
	go->GetComponent<dae::RenderComponent>()->SetZOrder(-1);
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


	const auto pooka = std::make_shared<dae::GameObject>();
	pooka->SetLocalPosition({ 216.f, 200.f, 0.f });
	pooka->AddComponent(std::make_unique<dae::RenderComponent>
		(
			pooka.get(), 
			dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png")
		)
	);

	pooka->AddComponent(std::make_unique<dae::StateComponent>
		(
			pooka.get(),
			new PatrollingState()
			)
	);
	scene.Add(pooka);


	const float speedP1{ 100.f };
	const float speedP2{ 200.f };


	const auto player1 = std::make_shared<dae::GameObject>();
	player1->SetLocalPosition({ 216.f, 180.f, 0.f });
	player1->AddComponent(std::make_unique<dae::RenderComponent>(player1.get(), dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png")));
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



	//////////////////
	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ReleaseButtonCommand>(),
		SDL_SCANCODE_D,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ReleaseButtonCommand>(),
		SDL_SCANCODE_A,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ReleaseButtonCommand>(),
		SDL_SCANCODE_W,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ReleaseButtonCommand>(),
		SDL_SCANCODE_S,
		dae::KeyState::Up
	);
	///////////////////




	const auto player2 = std::make_shared<dae::GameObject>();

	player2->SetLocalPosition({ 216.f, 180.f, 0.f });

	player2->AddComponent(std::make_unique<dae::RenderComponent>(
		player2.get(), 
		dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png")));

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


	//////////////////
	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ReleaseButtonCommand>(), 0,
		dae::ControllerInput::Gamepad_Dpad_Right,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ReleaseButtonCommand>(), 0,
		dae::ControllerInput::Gamepad_Dpad_Left,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ReleaseButtonCommand>(), 0,
		dae::ControllerInput::Gamepad_Dpad_Up,
		dae::KeyState::Up
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<ReleaseButtonCommand>(), 0,
		dae::ControllerInput::Gamepad_Dpad_Down,
		dae::KeyState::Up
	);
	///////////////////

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
	                                                                    "Using the D-Pad to move the yellow sprite and play walking music, X to inflict damage and play death sound, A and B To increase score."));
	scene.Add(controlsDisplay1);

	
	const auto controlsDisplay2 = std::make_shared<dae::GameObject>();

	controlsDisplay2->SetLocalPosition({ 0.f, 90.f, 0.f });

	controlsDisplay2->AddComponent(std::make_unique<dae::RenderComponent>(controlsDisplay2.get()));
	controlsDisplay2->AddComponent(std::make_unique<dae::TextComponent>(controlsDisplay2.get(), font,
	                                                                    "Using WASD to move the blue sprite and play walking music, C to inflict damage and play death sound, Z and X To increase score."));
	scene.Add(controlsDisplay2);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(InitializeGame);
	return 0;
}