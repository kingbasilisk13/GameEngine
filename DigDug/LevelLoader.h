#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

enum class GameMode;

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
	LevelLoader(dae::Scene* scene, const std::string& levelToLoad, GameMode gameMode);

	~LevelLoader();

	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) = delete;

private:
	bool m_AlreadySpawnedP1 = false;

	const int m_ReduceEnemyCollisionSize = 10;

	dae::Scene* m_Scene;

	GameMode m_GameMode;

	glm::ivec2 m_TileSize;

	glm::ivec2 m_Dimensions;

	std::vector<int> m_XValues;
	std::vector<int> m_YValues;

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
