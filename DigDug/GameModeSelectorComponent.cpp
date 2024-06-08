#include "GameModeSelectorComponent.h"

#include "InputManager.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "SkipLevelCommand.h"

GameModeSelectorComponent::GameModeSelectorComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{
}

void GameModeSelectorComponent::Update()
{
}

void GameModeSelectorComponent::FixedUpdate()
{
}

void GameModeSelectorComponent::Render() const
{
}

void GameModeSelectorComponent::SetSelectedGameMode(const GameMode gameMode)
{
	m_GameMode = gameMode;
}

void GameModeSelectorComponent::LoadLevelsBasedOnGameMode() const
{
	switch (m_GameMode)
	{
	case GameMode::singlePlayer:
		LoadSoloLevel();
		break;
	case GameMode::coOp:
		LoadCoopLevel();
		break;
	case GameMode::vS:
		LoadVsLevel();
		break;
	default: ;
	}
	
}

GameMode GameModeSelectorComponent::GetCurrentGameMode() const
{
	return m_GameMode;
}

void GameModeSelectorComponent::LoadSoloLevel() const
{
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("L1_1");
	auto temp1 = LevelLoader(&scene1, "../Data/Levels/L1_1.txt", m_GameMode);
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("L2_1");
	auto temp2 = LevelLoader(&scene2, "../Data/Levels/L2_1.txt", m_GameMode);
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("L3_1");
	auto temp3 = LevelLoader(&scene3, "../Data/Levels/L3_1.txt", m_GameMode);
	dae::SceneManager::GetInstance().OpenSceneByName("L1_1");
}

void GameModeSelectorComponent::LoadCoopLevel() const
{
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("L1_2");
	auto temp1 = LevelLoader(&scene1, "../Data/Levels/L1_2.txt", m_GameMode);
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("L2_2");
	auto temp2 = LevelLoader(&scene2, "../Data/Levels/L2_2.txt", m_GameMode);
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("L3_2");
	auto temp3 = LevelLoader(&scene3, "../Data/Levels/L3_2.txt", m_GameMode);
	dae::SceneManager::GetInstance().OpenSceneByName("L1_2");
}

void GameModeSelectorComponent::LoadVsLevel() const
{
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("L1_1");
	auto temp1 = LevelLoader(&scene1, "../Data/Levels/L1_1.txt", m_GameMode);
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("L2_1");
	auto temp2 = LevelLoader(&scene2, "../Data/Levels/L2_1.txt", m_GameMode);
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("L3_1");
	auto temp3 = LevelLoader(&scene3, "../Data/Levels/L3_1.txt", m_GameMode);
	dae::SceneManager::GetInstance().OpenSceneByName("L1_1");
}


