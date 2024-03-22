#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include<windows.h>
#include <Xinput.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "Scene.h"

#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "RenderComponent.h"

#include "Transform.h"

//this function creates a scene and adds the components to it.
void load()
{
	//todo: labo week 5, normaal zou enkel opdracht 1 en 2 nieuwe klassen nodig hebben. als je alles goed gemaakt hebt zou opdracht 3 enkel een paar enxtra lijnen code zijn.

	//todo: steam achievement is only for lab 5. after that you delete it.

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



	const float speedP1{ 100.f };
	const float speedP2{ 200.f };

	position.SetPosition({ 216.f, 180.f, 0.f });
	const auto player1 = std::make_shared<dae::GameObject>(position);
	player1->AddComponent(std::make_unique<dae::RenderComponent>(player1.get(), dae::ResourceManager::GetInstance().LoadTexture("Player1.png")));
	scene.Add(player1);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3(2, 0, 0), speedP1),
		SDL_SCANCODE_D,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3(-1, 0, 0), speedP1),
		SDL_SCANCODE_A,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3(0, -1, 0), speedP1),
		SDL_SCANCODE_W,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<dae::MoveCommand>(player1.get(), glm::vec3(0, 1, 0), speedP1),
		SDL_SCANCODE_S,
		dae::KeyState::Pressed
	);

	




	const auto player2 = std::make_shared<dae::GameObject>(position);
	player2->AddComponent(std::make_unique<dae::RenderComponent>(player2.get(), dae::ResourceManager::GetInstance().LoadTexture("Player2.png")));
	scene.Add(player2);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3(1, 0, 0), speedP2),
		0,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3(-1, 0, 0), speedP2),
		0,
		XINPUT_GAMEPAD_DPAD_LEFT,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3(0, -1, 0), speedP2),
		0,
		XINPUT_GAMEPAD_DPAD_UP,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<dae::MoveCommand>(player2.get(), glm::vec3(0, 1, 0), speedP2),
		0,
		XINPUT_GAMEPAD_DPAD_DOWN,
		dae::KeyState::Pressed
	);
}

int main(int, char*[]) {
	//creates the minigin
	dae::Minigin engine("../Data/");
	
	//adds a reference to the function load that can then be executed in the minigin run function.
	engine.Run(load);
    return 0;
}