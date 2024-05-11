#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void FixedUpdate() const;
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::vector < std::shared_ptr<GameObject>> GetObjectsInScene() const;

	private: 
		explicit Scene(std::string name);

		bool m_ObjectAreDirty;

		std::string m_Name;

		std::vector <GameObject*> m_RemovalList{};

		std::vector < std::shared_ptr<GameObject>> m_objects{};

		void HandleObjectRemoval();
	};

}
