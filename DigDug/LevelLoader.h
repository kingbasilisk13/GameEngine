#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
}

namespace dae
{
	class Scene;
}

class LevelLoader
{
public:
	LevelLoader(dae::Scene* scene, std::string levelToLoad);

	~LevelLoader();

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) = delete;

private:
	bool m_AlreadySpawnedP1 = false;

	dae::Scene* m_Scene;

	glm::ivec2 m_TileSize;

	glm::ivec2 m_Dimensions;

	const int m_Scale = 2;

	void ReadLevelFile(const std::string& levelToLoad);

	void AddTile(int x, int y) const;

	void AddTunnel(int x, int y, bool dugOut) const;

	void AddPlayer1(int x, int y);
	void AddPlayer2(int x, int y);

	void AddPooka(int x, int y) const;

	void AddFygar(int x, int y) const;

	void AddRock(int x, int y) const;


	void SetLocation(const std::shared_ptr<dae::GameObject>& object, int x, int y) const;
};


//todo: this is the code for 2 players

//void InitializePlayers(dae::Scene& scene)
//{
//	int width;
//	int height;
//
//	dae::Renderer::GetInstance().GetWindowSize(&width, &height);
//
//	width /= 2;
//	height /= 2;
//
//
//	//const float speedP1{ 100.f };
//	const float speedP2{ 100.f };
//
//
//	//const auto player1 = std::make_shared<dae::GameObject>("player1");
//	//player1->SetLocalPosition({ 216.f, 180.f });
//
//	//player1->AddComponent(
//	//	std::make_unique<dae::RenderComponent>(
//	//		player1.get(), 
//	//		dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png"
//	//		)
//	//	)
//	//);
//
//
//	//const auto renderComponent = player1->GetComponent<dae::RenderComponent>();
//
//	//const auto player1Size = dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png")->GetSize();
//
//	//renderComponent->SetZOrder(1);
//
//	//renderComponent->SizeToContent(false);
//
//	//renderComponent->SetDestinationSize(player1Size.x, player1Size.y*2);
//
//	//renderComponent->SetSourceValues(0, 0, player1Size.x / 2, player1Size.y);
//
//
//
//
//	//player1->AddComponent(std::make_unique<MovementComponent>(player1.get(), speedP1));
//	//player1->AddComponent(std::make_unique<HealthComponent>(player1.get(), 3));
//	//player1->AddComponent(std::make_unique<ScoreComponent>(player1.get()));
//	//scene.Add(player1);
//
//	//const auto component = player1->GetComponent<MovementComponent>();
//
//	//const auto healthComponentP1 = player1->GetComponent<HealthComponent>();
//
//	//const auto scoreComponentP1 = player1->GetComponent<ScoreComponent>();
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<KillCommand>(healthComponentP1),
//	//	SDL_SCANCODE_C,
//	//	dae::KeyState::Down
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ScoreCommand>(scoreComponentP1, 100),
//	//	SDL_SCANCODE_Z,
//	//	dae::KeyState::Down
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ScoreCommand>(scoreComponentP1, 10),
//	//	SDL_SCANCODE_X,
//	//	dae::KeyState::Down
//	//);
//
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<SetDirectionCommand>(component, glm::vec3(1, 0, 0)),
//	//	SDL_SCANCODE_D,
//	//	dae::KeyState::Pressed
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<SetDirectionCommand>(component, glm::vec3(-1, 0, 0)),
//	//	SDL_SCANCODE_A,
//	//	dae::KeyState::Pressed
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<SetDirectionCommand>(component, glm::vec3(0, -1, 0)),
//	//	SDL_SCANCODE_W,
//	//	dae::KeyState::Pressed
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<SetDirectionCommand>(component, glm::vec3(0, 1, 0)),
//	//	SDL_SCANCODE_S,
//	//	dae::KeyState::Pressed
//	//);
//
//
//
//	////////////////////
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ReleaseButtonCommand>(),
//	//	SDL_SCANCODE_D,
//	//	dae::KeyState::Up
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ReleaseButtonCommand>(),
//	//	SDL_SCANCODE_A,
//	//	dae::KeyState::Up
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ReleaseButtonCommand>(),
//	//	SDL_SCANCODE_W,
//	//	dae::KeyState::Up
//	//);
//
//	//dae::InputManager::GetInstance().AddKeyBinding(
//	//	std::make_unique<ReleaseButtonCommand>(),
//	//	SDL_SCANCODE_S,
//	//	dae::KeyState::Up
//	//);
//	/////////////////////
//
//
//
//
//	const auto player2 = std::make_shared<dae::GameObject>("player2");
//
//	player2->SetLocalPosition({ 216.f, 180.f });
//
//	player2->AddComponent(std::make_unique<dae::RenderComponent>(
//		player2.get(),
//		dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png")));
//
//	player2->AddComponent(std::make_unique<MovementComponent>(player2.get(), speedP2));
//	player2->AddComponent(std::make_unique<HealthComponent>(player2.get(), 3));
//	player2->AddComponent(std::make_unique<ScoreComponent>(player2.get()));
//	scene.Add(player2);
//
//	const auto temp = player2->GetComponent<MovementComponent>();
//
//	const auto healthComponentP2 = player2->GetComponent<HealthComponent>();
//
//	const auto scoreComponentP2 = player2->GetComponent<ScoreComponent>();
//
//
//	//todo: player controlles
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<KillCommand>(healthComponentP2),
//		0,
//		dae::ControllerInput::Gamepad_X,
//		dae::KeyState::Down
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ScoreCommand>(scoreComponentP2, 100),
//		0,
//		dae::ControllerInput::Gamepad_A,
//		dae::KeyState::Down
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ScoreCommand>(scoreComponentP2, 10),
//		0,
//		dae::ControllerInput::Gamepad_B,
//		dae::KeyState::Down
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<SetDirectionCommand>(temp, glm::vec3(1, 0, 0)),
//		0,
//		dae::ControllerInput::Gamepad_Dpad_Right,
//		dae::KeyState::Pressed
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<SetDirectionCommand>(temp, glm::vec3(-1, 0, 0)),
//		0,
//		dae::ControllerInput::Gamepad_Dpad_Left,
//		dae::KeyState::Pressed
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<SetDirectionCommand>(temp, glm::vec3(0, -1, 0)),
//		0,
//		dae::ControllerInput::Gamepad_Dpad_Up,
//		dae::KeyState::Pressed
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<SetDirectionCommand>(temp, glm::vec3(0, 1, 0)),
//		0,
//		dae::ControllerInput::Gamepad_Dpad_Down,
//		dae::KeyState::Pressed
//	);
//
//
//	//////////////////
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ReleaseButtonCommand>(), 0,
//		dae::ControllerInput::Gamepad_Dpad_Right,
//		dae::KeyState::Up
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ReleaseButtonCommand>(), 0,
//		dae::ControllerInput::Gamepad_Dpad_Left,
//		dae::KeyState::Up
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ReleaseButtonCommand>(), 0,
//		dae::ControllerInput::Gamepad_Dpad_Up,
//		dae::KeyState::Up
//	);
//
//	dae::InputManager::GetInstance().AddControllerBinding(
//		std::make_unique<ReleaseButtonCommand>(), 0,
//		dae::ControllerInput::Gamepad_Dpad_Down,
//		dae::KeyState::Up
//	);
//
//	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
//
//	////health display 1
//	//const auto player1HealthObserver = std::make_shared<dae::GameObject>("player1HealthObserver");
//
//	//player1HealthObserver->SetLocalPosition({ 0.f, 140.f});
//
//	//player1HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1HealthObserver.get()));
//	//player1HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player1HealthObserver.get(), font, "# lives: 3"));
//	//player1HealthObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player1HealthObserver.get()));
//	//scene.Add(player1HealthObserver);
//
//	//player1->GetComponent<HealthComponent>()->SubscribeToHealthChangedEvent(player1HealthObserver->GetComponent<PlayerObserverComponent>());
//
//
//	////score display 1
//	//const auto player1ScoreObserver = std::make_shared<dae::GameObject>("player1ScoreObserver");
//
//	//player1ScoreObserver->SetLocalPosition({ 0.f, 160.f});
//
//	//player1ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player1ScoreObserver.get()));
//	//player1ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player1ScoreObserver.get(), font, "Score: 0"));
//	//player1ScoreObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player1ScoreObserver.get()));
//	//scene.Add(player1ScoreObserver);
//
//	//player1->GetComponent<ScoreComponent>()->SubscribeToScoreChangedEvent(player1ScoreObserver->GetComponent<PlayerObserverComponent>());
//
//
//
//
//	////health display 2
//	//const auto player2HealthObserver = std::make_shared<dae::GameObject>("player2HealthObserver");
//
//	//player2HealthObserver->SetLocalPosition({ 0.f, 180.f});
//
//	//player2HealthObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2HealthObserver.get()));
//	//player2HealthObserver->AddComponent(std::make_unique<dae::TextComponent>(player2HealthObserver.get(), font, "# lives: 3"));
//	//player2HealthObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player2HealthObserver.get()));
//	//scene.Add(player2HealthObserver);
//
//	//player2->GetComponent<HealthComponent>()->SubscribeToHealthChangedEvent(player2HealthObserver->GetComponent<PlayerObserverComponent>());
//
//	////score display 2
//	//const auto player2ScoreObserver = std::make_shared<dae::GameObject>("player2ScoreObserver");
//
//	//player2ScoreObserver->SetLocalPosition({ 0.f, 200.f});
//
//	//player2ScoreObserver->AddComponent(std::make_unique<dae::RenderComponent>(player2ScoreObserver.get()));
//	//player2ScoreObserver->AddComponent(std::make_unique<dae::TextComponent>(player2ScoreObserver.get(), font, "Score: 0"));
//	//player2ScoreObserver->AddComponent(std::make_unique<PlayerObserverComponent>(player2ScoreObserver.get()));
//	//scene.Add(player2ScoreObserver);
//
//	//player2->GetComponent<ScoreComponent>()->SubscribeToScoreChangedEvent(player2ScoreObserver->GetComponent<PlayerObserverComponent>());
//
//
//}