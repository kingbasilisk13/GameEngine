#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <windows.h>

#include "BoxComponent.h"
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
#include "LevelLoader.h"
#include "LoggingSoundSystem.h"
#include "SetDirectionCommand.h"
#include "GridMovementComponent.h"
#include "MoveImageCommand.h"
#include "NullSoundSystem.h"
#include "PookaWanderState.h"
#include "PlayerObserverComponent.h"
#include "ReleaseButtonCommand.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "SdlSoundSystem.h"
#include "ServiceLocator.h"
#include "StateComponent.h"
#include "SkipLevelCommand.h"
#include "ToggleAudioCommand.h"
#include "Transform.h"


//todo: state moet beslisen naar waar het over gaat, event verandert de state niet. kan wel info geven.

void InitializeMusic()
{
#if _DEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SdlSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SdlSoundSystem>());
#endif

	//todo: je bent niet verplicht om dingen op specifieken manieren te doen. ze geven u de paterns, jij gebruikt ze hoe jij wilt, maar je moet kunnen uitleggen waarom.
	//todo: als je in uw if state class een in hebt die checkt voor een state gelijk aan x of niet dan kan het opgeslpits worden in 2 state classes.

	//todo: intead of using boxes to see if things overlap it is probalby a better idea to use raycasting. draw line from character in direction it is moving. if it hits a box then move in diferent direction.

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


	dae::ServiceLocator::GetSoundSystem().Initialize("../Data/Sound/", soundEffectList, musicList);


	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<ToggleAudioCommand>(),
		SDL_SCANCODE_M,
		dae::KeyState::Down
	);

}

void MainMenuCreator()
{
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	int width;
	int height;
	dae::Renderer::GetInstance().GetWindowSize(&width, &height);

	constexpr int scaleImage = 2;

	const auto background = std::make_shared<dae::GameObject>("background");
	auto position = background->GetWorldPosition();
	auto size = dae::ResourceManager::GetInstance().LoadTexture("MainMenu/Background.png")->GetSize();
	dae::RenderInfo renderInfo;
	renderInfo.destinationX = width / 2;
	renderInfo.destinationY = height / 2;
	renderInfo.destinationWidth = size.x * scaleImage;
	renderInfo.destinationHeight = size.y * scaleImage;
	renderInfo.sourceWidth = size.x;
	renderInfo.sourceHeight = size.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("MainMenu/Background.png");
	background->AddComponent(std::make_unique<dae::RenderComponent>(background.get(), renderInfo));
	mainMenu.Add(background);


	const auto arrow = std::make_shared<dae::GameObject>("arrow");
	position = arrow->GetWorldPosition();
	size = dae::ResourceManager::GetInstance().LoadTexture("MainMenu/Marker.png")->GetSize();

	const int xPosition = (width / 2) - 90;
	const int yPosition = (height / 2) + 18;
	constexpr int distanceBetweenOptions = 32;

	renderInfo.zOrder = 1;
	renderInfo.destinationX = xPosition;
	renderInfo.destinationY = yPosition - distanceBetweenOptions;
	renderInfo.destinationWidth = size.x * scaleImage;
	renderInfo.destinationHeight = size.y * scaleImage;
	renderInfo.sourceWidth = size.x;
	renderInfo.sourceHeight = size.y;
	renderInfo.textureToRender = dae::ResourceManager::GetInstance().LoadTexture("MainMenu/Marker.png");

	arrow->AddComponent(std::make_unique<dae::RenderComponent>(arrow.get(), renderInfo));

	auto renderComponent = arrow->GetComponent<dae::RenderComponent>();

	

	std::vector<glm::vec2> positionsArrayDown{};
	positionsArrayDown.emplace_back(xPosition, yPosition - distanceBetweenOptions);
	positionsArrayDown.emplace_back(xPosition, yPosition);
	positionsArrayDown.emplace_back(xPosition, yPosition+ distanceBetweenOptions);

	std::vector<glm::vec2> positionsArrayUp{};
	positionsArrayUp.emplace_back(xPosition, yPosition + distanceBetweenOptions);
	positionsArrayUp.emplace_back(xPosition, yPosition);
	positionsArrayUp.emplace_back(xPosition, yPosition - distanceBetweenOptions);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<MoveImageCommand>(renderComponent,"MainMenu", positionsArrayUp),
		SDL_SCANCODE_W,
		dae::KeyState::Down
	);

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<MoveImageCommand>(renderComponent, "MainMenu", positionsArrayDown),
		SDL_SCANCODE_S,
		dae::KeyState::Down
	);

	mainMenu.Add(arrow);

}



void InitializeGame()
{
	InitializeMusic();

	MainMenuCreator();

	dae::SceneManager::GetInstance().OpenSceneByName("MainMenu");

	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("L1_1");
	auto temp1 = LevelLoader(&scene1, "../Data/Levels/L1_1.txt");

	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("L2_1");
	auto temp2 =LevelLoader(&scene2, "../Data/Levels/L2_1.txt");

	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("L3_1");
	auto temp3 = LevelLoader(&scene3, "../Data/Levels/L3_1.txt");

	std::vector<std::string> level = {"L1_1","L2_1","L3_1"};

	dae::InputManager::GetInstance().AddKeyBinding(
		std::make_unique<SkipLevelCommand>(level),
		SDL_SCANCODE_F1,
		dae::KeyState::Down
	);
}

int main(int, char* []) {

	//todo: alle textures moeten groter gezet worden. 2maal zo groot.
	dae::Minigin engine("../Data/", 512, 448);

	engine.Run(InitializeGame);
	return 0;
}