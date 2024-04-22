#pragma once
#include <vector>
#include <string>
#include <memory>
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

		//only used for physics an networking.
		void FixedUpdate();

		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
