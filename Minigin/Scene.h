#pragma once
#include <functional>

#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
		friend void dae::SceneManager::OpenSceneByName(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void FixedUpdate() const;
		void Render() const;

		

		[[nodiscard]] std::vector < std::shared_ptr<GameObject>> GetObjectsInScene() const;
		[[nodiscard]] std::vector < std::shared_ptr<GameObject>> GetObjectsByName(std::string name) const;
		[[nodiscard]] std::shared_ptr<GameObject> GetObjectByName(std::string name) const;

		[[nodiscard]] std::string GetSceneName() const;

		void AddOnLevelLoudFunction(const std::function<void()>& function);


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private: 
		explicit Scene(std::string name);

		bool m_ObjectAreDirty;

		std::string m_Name;

		std::vector <GameObject*> m_RemovalList{};

		std::vector < std::shared_ptr<GameObject>> m_objects{};

		//functions that will be executed the moment the scene becomes active.
		std::vector<std::function<void()>>  m_OnSceneActiveFunctions;

		//should only be executed by the scene manager
		void ExecuteOnLevelLoadFunctions() const;

		void HandleObjectRemoval();
	};

}
