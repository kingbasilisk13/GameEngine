#include "LevelLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "AnimationComponent.h"
#include "BoxComponent.h"
#include "BoxDeletionComponent.h"
#include "ControllerInput.h"
#include "EnemyAttackComponent.h"
#include "FygarWanderState.h"
#include "GameModeSelectorComponent.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "PookaWanderState.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "StateComponent.h"
#include "GridMovementComponent.h"
#include "PlayerWalkingState.h"
#include "RegisterInputCommand.h"
#include "ScoreComponent.h"
#include "SetDirectionCommand.h"
#include "ReleaseButtonCommand.h"
#include "ResetPositionComponent.h"

LevelLoader::LevelLoader(dae::Scene* scene, const std::string& levelToLoad, const GameMode gameMode)
	:m_Scene(scene)
	, m_GameMode(gameMode)
	, m_TileSize(dae::ResourceManager::GetInstance().LoadTexture("Tiles/WorldTile0.png")->GetSize())
{
	int width;
	int height;
	dae::Renderer::GetInstance().GetWindowSize(&width, &height);

	m_TileSize *= m_Scale;

	m_Dimensions.x = m_TileSize.x / 2;
	m_Dimensions.y = (height) - (m_TileSize.y * 11) - (m_TileSize.y/2);


	ReadLevelFile(levelToLoad);
}

LevelLoader::~LevelLoader() = default;

void LevelLoader::ReadLevelFile(const std::string& levelToLoad)
{
    std::ifstream file(levelToLoad);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << levelToLoad << '\n';
        return;
    }

    std::vector<std::string> lines;

    std::string line;
    while (std::getline(file, line)) 
	{
        lines.push_back(line);
    }

	//12x12 grid

	for(int i = 0; i < 12; ++i)
	{
		m_XValues.push_back((m_Dimensions.x + (i * m_TileSize.x)));
		m_YValues.push_back((m_Dimensions.y + (i * m_TileSize.y)));
	}

    for(int y = 0; y < static_cast<int>(lines.size()); ++y)
    {
		int x = 0;
        for (char c : lines[y]) 
		{
			AddTile(x, y);

			if (c == '0')
			{
				AddTunnel(x, y,true);
			}
            else if(c == '1')
            {
				AddTunnel(x, y, false);
            }
        	else if (c == '2')
            {
				AddTunnel(x, y, false);
				AddRock(x, y);
            }
			else if (c == '3')
			{
				AddTunnel(x, y, true);
				AddPooka(x, y);
			}
			else if (c == '4')
			{
				AddTunnel(x, y, true);
				AddFygar(x,y);
			}
			else if (c == '5')
			{
				AddTunnel(x, y, true);
				if(m_AlreadySpawnedP1)
				{
					AddPlayer2(x, y);
				}
				else
				{
					AddPlayer1(x, y);
				}
				
			}

			++x;
        }
    }
    file.close();
}


void LevelLoader::AddTile(int x, int y) const
{
	std::string texture;

	if (y < 3)
	{
		texture = "Tiles/WorldTile0.png";
	}
	else if (y < 6)
	{
		texture = "Tiles/WorldTile1.png";
	}
	else if (y < 9)
	{
		texture = "Tiles/WorldTile2.png";
	}
	else
	{
		texture = "Tiles/WorldTile3.png";
	}

	const auto tile = std::make_shared<dae::GameObject>("tile");

	SetLocation(tile, x, y);

	const auto position = tile->GetWorldPosition();

	const auto size = dae::ResourceManager::GetInstance().LoadTexture(texture)->GetSize();

	dae::RenderInfo renderInfo;
	renderInfo.zOrder = 0;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = m_TileSize.x;
	renderInfo.destinationHeight = m_TileSize.y;
	renderInfo.sourceX = 0;
	renderInfo.sourceY = 0;
	renderInfo.sourceWidth = size.x;
	renderInfo.sourceHeight = size.y;
	renderInfo.angle = 0;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture(texture);
	renderInfo.imageFlip = dae::FlipImage::None;

	tile->AddComponent(std::make_unique<dae::RenderComponent>(tile.get(), renderInfo));

	m_Scene->Add(tile);
}


void LevelLoader::AddTunnel(const int x, const int y, const bool dugOut) const
{
	const auto tunnel = std::make_shared<dae::GameObject>("tunnel");

	SetLocation(tunnel, x, y);

	const auto size = dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png")->GetSize();

	const auto position = tunnel->GetWorldPosition();

	dae::RenderInfo renderInfo;

	if(dugOut)
	{

		renderInfo.zOrder = 1;
		renderInfo.destinationX = static_cast<int>(position.x);
		renderInfo.destinationY = static_cast<int>(position.y);
		renderInfo.destinationWidth = size.x * m_Scale;
		renderInfo.destinationHeight = size.y * m_Scale;
		renderInfo.sourceX = 0;
		renderInfo.sourceY = 0;
		renderInfo.sourceWidth = size.x;
		renderInfo.sourceHeight = size.y;
		renderInfo.angle = 0;
		renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png");
		renderInfo.imageFlip = dae::FlipImage::None;

		tunnel->AddComponent(std::make_unique<dae::RenderComponent>(tunnel.get(), renderInfo));

	}
	else
	{
		renderInfo.zOrder = 1;
		renderInfo.destinationX = static_cast<int>(position.x);
		renderInfo.destinationY = static_cast<int>(position.y);
		renderInfo.destinationWidth = size.x * m_Scale;
		renderInfo.destinationHeight = size.y * m_Scale;
		renderInfo.sourceX = 0;
		renderInfo.sourceY = 0;
		renderInfo.sourceWidth = 0;
		renderInfo.sourceHeight = 0;
		renderInfo.angle = 0;
		renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png");
		renderInfo.imageFlip = dae::FlipImage::None;

		tunnel->AddComponent(std::make_unique<dae::RenderComponent>(tunnel.get(), renderInfo));

		tunnel->AddComponent(std::make_unique<dae::BoxComponent>
			(
				tunnel.get(),
				static_cast<float>(m_TileSize.x),
				static_cast<float>(m_TileSize.y)
			)
		);

		tunnel->AddComponent(std::make_unique<BoxDeletionComponent>(tunnel.get(),m_GameMode));
	}

	m_Scene->Add(tunnel);
}

void LevelLoader::AddPlayer1(const int x, const int y)
{
	const float speed{ 50.f };

	const auto player1 = std::make_shared<dae::GameObject>("player1");

	SetLocation(player1, x, y);

	const auto player1Size = dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png")->GetSize();

	const int tempWidth = player1Size.x / 2;

	const auto position = player1->GetWorldPosition();
	dae::RenderInfo renderInfo;
	renderInfo.zOrder = 2;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = tempWidth * m_Scale;
	renderInfo.destinationHeight = player1Size.y * m_Scale;
	renderInfo.sourceWidth = tempWidth;
	renderInfo.sourceHeight = player1Size.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png");
	renderInfo.imageFlip = dae::FlipImage::None;

	player1->AddComponent(std::make_unique<dae::RenderComponent>(player1.get(), renderInfo));

	player1->AddComponent(std::make_unique<dae::AnimationComponent>(
		player1.get(),
		0.5f,
		1,
		2));

	player1->AddComponent(std::make_unique<ResetPositionComponent>(player1.get(), player1.get()->GetWorldPosition()));

	player1->AddComponent(std::make_unique<GridMovementComponent>(player1.get(), speed));

	const auto movementComponent = player1->GetComponent<GridMovementComponent>();

	glm::vec2 tL{};
	tL.x = static_cast<float>(m_XValues[0]);
	tL.y = static_cast<float>(m_YValues[0]);

	glm::vec2 bR{};
	bR.x = static_cast<float>(m_XValues[11]);
	bR.y = static_cast<float>(m_YValues[11]);

	movementComponent->SetBounds(tL,bR);
	movementComponent->SetGridValues(m_XValues, m_YValues);

	player1->AddComponent(std::make_unique<HealthComponent>(player1.get(), 3));

	player1->AddComponent(std::make_unique<dae::StateComponent>(player1.get(), new PlayerWalkingState(PlayerInput::right, dae::FlipImage::None)));

	//todo: may need to remove this component.
	player1->AddComponent(std::make_unique<ScoreComponent>(player1.get()));

	player1->AddComponent(std::make_unique<dae::BoxComponent>
		(
			player1.get(),
			static_cast<float>(m_TileSize.x/2),
			static_cast<float>(m_TileSize.y/2)
		)
	);

	m_Scene->Add(player1);

	const auto sceneName = m_Scene->GetSceneName();

#pragma region movement
	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(movementComponent, sceneName,glm::vec3(1, 0, 0)),
		SDL_SCANCODE_D,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec3(-1, 0, 0)),
		SDL_SCANCODE_A,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec3(0, -1, 0)),
		SDL_SCANCODE_W,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec3(0, 1, 0)),
		SDL_SCANCODE_S,
		dae::KeyState::Pressed
	);
#pragma endregion movement


	const auto stateComponent = player1->GetComponent<dae::StateComponent>();

#pragma region input
	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName,PlayerInput::right),
		SDL_SCANCODE_D,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::left),
		SDL_SCANCODE_A,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::up),
		SDL_SCANCODE_W,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::down),
		SDL_SCANCODE_S,
		dae::KeyState::Pressed
	);
#pragma endregion input

	m_AlreadySpawnedP1 = true;

	switch (m_GameMode)
	{
	case GameMode::singlePlayer:
#pragma region movement
		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(1, 0)),
			0,
			dae::ControllerInput::Gamepad_Dpad_Right,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(-1, 0)),
			0,
			dae::ControllerInput::Gamepad_Dpad_Left,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(0, -1)),
			0,
			dae::ControllerInput::Gamepad_Dpad_Up,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(0, 1)),
			0,
			dae::ControllerInput::Gamepad_Dpad_Down,
			dae::KeyState::Pressed
		);
#pragma endregion movement
#pragma region input
		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::right),
			0,
			dae::ControllerInput::Gamepad_Dpad_Right,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::left),
			0,
			dae::ControllerInput::Gamepad_Dpad_Left,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::up),
			0,
			dae::ControllerInput::Gamepad_Dpad_Up,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::down),
			0,
			dae::ControllerInput::Gamepad_Dpad_Down,
			dae::KeyState::Pressed
		);
#pragma endregion input
		break;

	case GameMode::coOp:
#pragma region movement
		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(1, 0)),
			1,
			dae::ControllerInput::Gamepad_Dpad_Right,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(-1, 0)),
			1,
			dae::ControllerInput::Gamepad_Dpad_Left,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(0, -1)),
			1,
			dae::ControllerInput::Gamepad_Dpad_Up,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<SetDirectionCommand>(movementComponent, sceneName, glm::vec2(0, 1)),
			1,
			dae::ControllerInput::Gamepad_Dpad_Down,
			dae::KeyState::Pressed
		);
#pragma endregion movement
#pragma region input
		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::right),
			1,
			dae::ControllerInput::Gamepad_Dpad_Right,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::left),
			1,
			dae::ControllerInput::Gamepad_Dpad_Left,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::up),
			1,
			dae::ControllerInput::Gamepad_Dpad_Up,
			dae::KeyState::Pressed
		);

		dae::InputManager::GetInstance().AddControllerBinding(
			std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::down),
			1,
			dae::ControllerInput::Gamepad_Dpad_Down,
			dae::KeyState::Pressed
		);
#pragma endregion input
		break;
	}

}


void LevelLoader::AddPlayer2(const int x, const int y)
{
	const float speed{ 50.f };

	const auto player2 = std::make_shared<dae::GameObject>("player2");

	SetLocation(player2, x, y);

	const auto player2Size = dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png")->GetSize();

	const int tempWidth = player2Size.x / 2;

	const auto position = player2->GetWorldPosition();
	dae::RenderInfo renderInfo{};
	renderInfo.zOrder = 2;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = tempWidth * m_Scale;
	renderInfo.destinationHeight = player2Size.y * m_Scale;
	renderInfo.sourceWidth = tempWidth;
	renderInfo.sourceHeight = player2Size.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png");

	player2->AddComponent(std::make_unique<ResetPositionComponent>(player2.get(), player2.get()->GetWorldPosition()));

	player2->AddComponent(std::make_unique<dae::RenderComponent>(player2.get(), renderInfo));

	player2->AddComponent(std::make_unique<dae::AnimationComponent>(
		player2.get(),
		0.5f,
		1,
		2));

	player2->AddComponent(std::make_unique<GridMovementComponent>(player2.get(), speed));
	const auto movementComponent = player2->GetComponent<GridMovementComponent>();
	glm::vec2 tL{};
	tL.x = static_cast<float>(m_XValues[0]);
	tL.y = static_cast<float>(m_YValues[0]);
	glm::vec2 bR{};
	bR.x = static_cast<float>(m_XValues[11]);
	bR.y = static_cast<float>(m_YValues[11]);
	movementComponent->SetBounds(tL, bR);
	movementComponent->SetGridValues(m_XValues, m_YValues);

	player2->AddComponent(std::make_unique<HealthComponent>(player2.get(), 3));

	player2->AddComponent(std::make_unique<dae::StateComponent>(player2.get(), new PlayerWalkingState(PlayerInput::right, dae::FlipImage::None)));

	player2->AddComponent(std::make_unique<dae::BoxComponent>
		(
			player2.get(),
			static_cast<float>(m_TileSize.x / 2),
			static_cast<float>(m_TileSize.y / 2)
		)
	);
	
	m_Scene->Add(player2);

	const auto component = player2->GetComponent<GridMovementComponent>();

	const auto sceneName = m_Scene->GetSceneName();

#pragma region movement
	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, sceneName, glm::vec2(1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Right,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, sceneName, glm::vec2(-1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Left,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, sceneName, glm::vec2(0, -1)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Up,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, sceneName, glm::vec2(0, 1)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Down,
		dae::KeyState::Pressed
	);
#pragma endregion movement
	const auto stateComponent = player2->GetComponent<dae::StateComponent>();

#pragma region input
	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::right),
		0,
		dae::ControllerInput::Gamepad_Dpad_Right,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::left),
		0,
		dae::ControllerInput::Gamepad_Dpad_Left,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::up),
		0,
		dae::ControllerInput::Gamepad_Dpad_Up,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<RegisterInputCommand>(stateComponent, sceneName, PlayerInput::down),
		0,
		dae::ControllerInput::Gamepad_Dpad_Down,
		dae::KeyState::Pressed
	);
#pragma endregion input
}


void LevelLoader::AddPooka(const int x, const int y) const
{
	const auto pooka = std::make_shared<dae::GameObject>("pooka");

	SetLocation(pooka, x, y);

	const auto pookaSize = dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png")->GetSize();
	const int tempWidth = static_cast<int>(pookaSize.x * 0.5f);

	const auto position = pooka->GetWorldPosition();
	dae::RenderInfo renderInfo{};
	renderInfo.zOrder = 2;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = tempWidth * m_Scale;
	renderInfo.destinationHeight = pookaSize.y * m_Scale;
	renderInfo.sourceWidth = tempWidth;
	renderInfo.sourceHeight = pookaSize.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png");
	renderInfo.imageFlip = dae::FlipImage::None;

	pooka->AddComponent(std::make_unique<ResetPositionComponent>(pooka.get(), pooka.get()->GetWorldPosition()));

	pooka->AddComponent(std::make_unique<dae::RenderComponent>(pooka.get(), renderInfo));

	pooka->AddComponent(std::make_unique<EnemyAttackComponent>(pooka.get()));

	pooka->AddComponent(std::make_unique<dae::AnimationComponent>(
		pooka.get(),
		0.5f,
		1,
		2));


	pooka->AddComponent(std::make_unique<dae::StateComponent>(pooka.get(),	new PookaWanderState()));

	pooka->AddComponent(std::make_unique<GridMovementComponent>(pooka.get(), 40.f));
	const auto movementComponent = pooka->GetComponent<GridMovementComponent>();
	glm::vec2 tL{};
	tL.x = static_cast<float>(m_XValues[0]);
	tL.y = static_cast<float>(m_YValues[0]);
	glm::vec2 bR{};
	bR.x = static_cast<float>(m_XValues[11]);
	bR.y = static_cast<float>(m_YValues[11]);
	movementComponent->SetBounds(tL, bR);
	movementComponent->SetGridValues(m_XValues, m_YValues);

	float size = static_cast<float>(pookaSize.y);

	pooka->AddComponent(std::make_unique<dae::BoxComponent>
		(
			pooka.get(),
			(size* m_Scale)-5,
			(size* m_Scale)-5
		)
	);

	
	m_Scene->Add(pooka);
}

void LevelLoader::AddFygar(const int x, const int y) const
{
	const auto fygar = std::make_shared<dae::GameObject>("fygar");

	SetLocation(fygar, x, y);

	const auto fygarSize = dae::ResourceManager::GetInstance().LoadTexture("Fygar/Default.png")->GetSize();
	const int tempWidth = static_cast<int>(fygarSize.x * 0.5f);

	const auto position = fygar->GetWorldPosition();
	dae::RenderInfo renderInfo{};
	renderInfo.zOrder = 2;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = tempWidth * m_Scale;
	renderInfo.destinationHeight = fygarSize.y * m_Scale;
	renderInfo.sourceWidth = tempWidth;
	renderInfo.sourceHeight = fygarSize.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("Fygar/Default.png");
	renderInfo.imageFlip = dae::FlipImage::None;

	fygar->AddComponent(std::make_unique<dae::RenderComponent>(fygar.get(), renderInfo));

	fygar->AddComponent(std::make_unique<ResetPositionComponent>(fygar.get(), fygar.get()->GetWorldPosition()));

	fygar->AddComponent(std::make_unique<EnemyAttackComponent>(fygar.get()));

	fygar->AddComponent(std::make_unique<dae::AnimationComponent>(
		fygar.get(),
		0.5f,
		1,
		2));
	

	fygar->AddComponent(std::make_unique<dae::StateComponent>
		(
			fygar.get(),
			new FygarWanderState()
		)
	);


	fygar->AddComponent(std::make_unique<GridMovementComponent>(fygar.get(), 40.f));
	const auto movementComponent = fygar->GetComponent<GridMovementComponent>();
	glm::vec2 tL{};
	tL.x = static_cast<float>(m_XValues[0]);
	tL.y = static_cast<float>(m_YValues[0]);
	glm::vec2 bR{};
	bR.x = static_cast<float>(m_XValues[11]);
	bR.y = static_cast<float>(m_YValues[11]);
	movementComponent->SetBounds(tL, bR);
	movementComponent->SetGridValues(m_XValues, m_YValues);


	float size = static_cast<float>(fygarSize.y);
	fygar->AddComponent(std::make_unique<dae::BoxComponent>
		(
			fygar.get(),
			size,
			size
		)
	);

	m_Scene->Add(fygar);
}

void LevelLoader::AddRock(const int x, const int y) const
{

	const auto rock = std::make_shared<dae::GameObject>("Rock");

	SetLocation(rock, x, y);

	const auto size = dae::ResourceManager::GetInstance().LoadTexture("Rock/RockDefault.png")->GetSize();

	const auto position = rock->GetWorldPosition();
	dae::RenderInfo renderInfo{};
	renderInfo.zOrder = 2;
	renderInfo.destinationX = static_cast<int>(position.x);
	renderInfo.destinationY = static_cast<int>(position.y);
	renderInfo.destinationWidth = size.x * m_Scale;
	renderInfo.destinationHeight = size.y * m_Scale;
	renderInfo.sourceWidth = size.x;
	renderInfo.sourceHeight = size.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("Rock/RockDefault.png");
	renderInfo.imageFlip = dae::FlipImage::None;

	rock->AddComponent(std::make_unique<dae::RenderComponent>(rock.get(), renderInfo));

	rock->AddComponent(std::make_unique<dae::BoxComponent>
		(
			rock.get(),
			static_cast<float>(m_TileSize.x - 1),
			static_cast<float>(m_TileSize.y - 1)
		)
	);
	m_Scene->Add(rock);
}

void LevelLoader::SetLocation(const std::shared_ptr<dae::GameObject>& object, int x, int y) const
{
	object->SetLocalPosition(
		{
			m_Dimensions.x + (x * m_TileSize.x),
			m_Dimensions.y + (y * m_TileSize.y)
		}
	);
}



