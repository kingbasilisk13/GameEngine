#include "LevelLoader.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "BoxComponent.h"
#include "ControllerInput.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "KillCommand.h"
#include "PatrollingState.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "StateComponent.h"
#include "MovementComponent.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "SetDirectionCommand.h"
#include "ReleaseButtonCommand.h"

LevelLoader::LevelLoader(dae::Scene* scene, std::string levelToLoad)
	:m_Scene(scene)
	,m_TileSize(dae::ResourceManager::GetInstance().LoadTexture("Tiles/WorldTile0.png")->GetSize())
{
	int width;
	int height;
	dae::Renderer::GetInstance().GetWindowSize(&width, &height);

	m_TileSize *= m_Scale;

	m_Dimensions.x = 0;
	m_Dimensions.y = (height) - (m_TileSize.y * 12);


	ReadLevelFile(levelToLoad);
}

LevelLoader::~LevelLoader() = default;

void LevelLoader::ReadLevelFile(const std::string& levelToLoad)
{
    std::ifstream file(levelToLoad);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << levelToLoad << std::endl;
        return;
    }

    std::vector<std::string> lines;

    std::string line;
    while (std::getline(file, line)) 
	{
        lines.push_back(line);
    }

    for(int y = 0; y < lines.size(); ++y)
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
	std::string texture = "";

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

	const auto size = dae::ResourceManager::GetInstance().LoadTexture(texture)->GetSize();

	tile->AddComponent(std::make_unique<dae::RenderComponent>
		(
			tile.get(),
			0,
			m_TileSize.x,
			m_TileSize.y,
			0,
			0,
			size.x,
			size.y,
			dae::ResourceManager::GetInstance().LoadTexture(texture)
		)
	);

	m_Scene->Add(tile);
}


void LevelLoader::AddTunnel(int x, int y, bool dugOut) const
{
	const auto tunnel = std::make_shared<dae::GameObject>("tunnel");

	SetLocation(tunnel, x, y);

	const auto size = dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png")->GetSize();

	if(dugOut)
	{
		tunnel->AddComponent(std::make_unique<dae::RenderComponent>
			(
				tunnel.get(),
				1,
				size.x * m_Scale,
				size.y * m_Scale,
				0,
				0,
				size.x,
				size.y,
				dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png")
			)
		);

		/*tunnel->AddComponent(std::make_unique<dae::BoxComponent>
			(
				tunnel.get(),
				static_cast<float>(0),
				static_cast<float>(0)
			)
		);*/

	}
	else
	{
		tunnel->AddComponent(std::make_unique<dae::RenderComponent>
			(
				tunnel.get(),
				1,
				m_TileSize.x * m_Scale,
				m_TileSize.y * m_Scale,
				0,
				0,
				0,
				0,
				dae::ResourceManager::GetInstance().LoadTexture("DiggedArea.png")
			)
		);

		tunnel->AddComponent(std::make_unique<dae::BoxComponent>
			(
				tunnel.get(),
				static_cast<float>(m_TileSize.x),
				static_cast<float>(m_TileSize.y)
			)
		);
	}

	m_Scene->Add(tunnel);
}

void LevelLoader::AddPlayer1(const int x, const int y)
{
	const float speed{ 50.f };

	const auto player1 = std::make_shared<dae::GameObject>("player1");

	SetLocation(player1, x, y);

	const auto player1Size = dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png")->GetSize();

	const int tempWidth = static_cast<int>(player1Size.x * 0.5f);

	player1->AddComponent(
		std::make_unique<dae::RenderComponent>(
			player1.get(),
			2,
			tempWidth * m_Scale, 
			player1Size.y * m_Scale,
			0,
			0,
			tempWidth, 
			player1Size.y,
			dae::ResourceManager::GetInstance().LoadTexture("DigDug0/Walking.png"
			)
		)
	);


	player1->AddComponent(std::make_unique<MovementComponent>(player1.get(), speed));
	player1->AddComponent(std::make_unique<HealthComponent>(player1.get(), 3));
	player1->AddComponent(std::make_unique<ScoreComponent>(player1.get()));
	m_Scene->Add(player1);

	const auto component = player1->GetComponent<MovementComponent>();

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

	m_AlreadySpawnedP1 = true;
}


void LevelLoader::AddPlayer2(const int x, const int y)
{
	const float speed{ 50.f };

	const auto player2 = std::make_shared<dae::GameObject>("player2");

	SetLocation(player2, x, y);

	const auto player2Size = dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png")->GetSize();

	const int tempWidth = static_cast<int>(player2Size.x * 0.5f);

	player2->AddComponent(
		std::make_unique<dae::RenderComponent>(
			player2.get(),
			2,
			tempWidth * m_Scale,
			player2Size.y * m_Scale,
			0,
			0,
			tempWidth,
			player2Size.y,
			dae::ResourceManager::GetInstance().LoadTexture("DigDug1/Walking.png"
			)
		)
	);


	player2->AddComponent(std::make_unique<MovementComponent>(player2.get(), speed));
	player2->AddComponent(std::make_unique<HealthComponent>(player2.get(), 3));
	player2->AddComponent(std::make_unique<ScoreComponent>(player2.get()));
	m_Scene->Add(player2);

	const auto component = player2->GetComponent<MovementComponent>();

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(1, 0, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Right,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(-1, 0, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Left,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(0, -1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Up,
		dae::KeyState::Pressed
	);

	dae::InputManager::GetInstance().AddControllerBinding(
		std::make_unique<SetDirectionCommand>(component, glm::vec3(0, 1, 0)),
		0,
		dae::ControllerInput::Gamepad_Dpad_Down,
		dae::KeyState::Pressed
	);

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
}


void LevelLoader::AddPooka(const int x, const int y) const
{
	const auto pooka = std::make_shared<dae::GameObject>("pooka");

	SetLocation(pooka, x, y);

	const auto pookaSize = dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png")->GetSize();
	const int tempWidth = static_cast<int>(pookaSize.x * 0.5f);

	pooka->AddComponent(std::make_unique<dae::RenderComponent>
		(
			pooka.get(),
			2,
			(tempWidth * m_Scale) - 2, 
			(pookaSize.y * m_Scale) - 2,
			0,
			0,
			tempWidth, 
			pookaSize.y,
			dae::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png")
		)
	);

	pooka->AddComponent(std::make_unique<dae::StateComponent>
		(
			pooka.get(),
			new PatrollingState()
		)
	);
	float size = static_cast<float>(pookaSize.y);

	pooka->AddComponent(std::make_unique<dae::BoxComponent>
		(
			pooka.get(),
			(size * m_Scale) - 2,
			(size * m_Scale) - 2
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

	fygar->AddComponent(std::make_unique<dae::RenderComponent>
		(
			fygar.get(),
			2,
			(tempWidth * m_Scale) - 2,
			(fygarSize.y * m_Scale) - 2,
			0,
			0,
			tempWidth, 
			fygarSize.y,
			dae::ResourceManager::GetInstance().LoadTexture("Fygar/Default.png")
		)
	);

	//todo: dont you just hate it when you need to repeat code.

	fygar->AddComponent(std::make_unique<dae::StateComponent>
		(
			fygar.get(),
			new PatrollingState()
		)
	);
	float size = static_cast<float>(fygarSize.y);

	fygar->AddComponent(std::make_unique<dae::BoxComponent>
		(
			fygar.get(),
			(size * m_Scale) - 2,
			(size * m_Scale) - 2
		)
	);

	m_Scene->Add(fygar);
}

void LevelLoader::AddRock(const int x, const int y) const
{

	const auto rock = std::make_shared<dae::GameObject>("Rock");

	SetLocation(rock, x, y);

	const auto size = dae::ResourceManager::GetInstance().LoadTexture("Rock/RockDefault.png")->GetSize();

	rock->AddComponent(std::make_unique<dae::RenderComponent>
		(
			rock.get(),
			2,
			size.x * m_Scale,
			size.y * m_Scale,
			0,
			0,
			size.x,
			size.y,
			dae::ResourceManager::GetInstance().LoadTexture("Rock/RockDefault.png")
		)
	);

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



