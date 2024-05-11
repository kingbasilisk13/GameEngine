#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Texture2D.h"
#include "BaseComponent.h"
#include <iostream>

namespace dae
{
	class Scene;
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:
		explicit GameObject(std::string name);

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate() const;
		void Render() const;

		void SetScene(Scene* scene);
		[[nodiscard]] Scene* GetScene() const;

#pragma region component functions
		void AddComponent(std::unique_ptr<BaseComponent> component);

		void RemoveComponent(BaseComponent* component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		bool HasComponent();
#pragma endregion

#pragma region parent child and location functions
		[[nodiscard]] GameObject* GetParentGameObject() const { return m_Parent; }

		void SetParentGameObject(GameObject* parentObject, bool keepWorldPosition = false);

		[[nodiscard]] size_t GetChildCount() const { return m_Children.size(); }

		[[nodiscard]] GameObject* GetChildAt(const int index)const { return m_Children[index]; }

		void SetLocalPosition(const glm::vec2& position);

		glm::vec2 GetWorldPosition();

		void SetPositionDirty();

		void Translate(glm::vec2 deltaMovement);
#pragma endregion 

		[[nodiscard]] bool IsPositionDirty() const
		{
			return m_PositionIsDirty;
		}

		std::string GetObjectName();
		

	private:
		bool m_PositionIsDirty;

		bool m_RemovalListIsDirty;

		//todo: this could be replaced by a check if object is of type, but is good enough for now.
		std::string m_ObjectName;

		
		//it has a local transform and a world transform
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};

		Scene* m_Scene;

		GameObject* m_Parent;

		std::vector <std::unique_ptr<BaseComponent>> m_Components{};

		std::vector<BaseComponent*> m_RemovalList{};

		std::vector<GameObject*> m_Children{};

#pragma region private functions
		void AddChild(GameObject* child) { m_Children.push_back(child); }

		void RemoveChild(GameObject* child);

		bool IsChild(GameObject* gameObject);

		void UpdateWorldPosition();

		void HandleComponentRemoval();
#pragma endregion 
	};

	//template functions

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& component : m_Components) {
			if (auto ptr = dynamic_cast<T*>(component.get())) {
				return ptr;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline bool GameObject::HasComponent()
	{
		return GetComponent<T>() != nullptr;
	}
}
