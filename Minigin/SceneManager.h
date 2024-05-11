#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"

//todo: add rule of five to all singletons and delete them

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();

		//only used for physics and networking.
		void FixedUpdate();

		void Render();

		void OpenSceneByName(std::string name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::string m_ActiveScene;

		std::unordered_map<std::string, std::shared_ptr<Scene>> m_MapOfScenes;

	};
}
