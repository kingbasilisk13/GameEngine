#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

#include "Texture2D.h"
namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:
		//todo: initialize variables in order of decleration.
		explicit GameObject(const Transform& transform);

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

#pragma region component functions
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(const std::shared_ptr<BaseComponent>& component);

		template<typename T>
		std::shared_ptr<T> GetComponent();

		template<typename T>
		bool HasComponent();
#pragma endregion

#pragma region parent child and location functions
		GameObject* GetParentGameObject() const { return m_Parent; }

		void SetParentGameObject(GameObject* parentObject, bool keepWorldPosition = false);

		size_t GetChildCount() const { return m_Children.size(); }

		GameObject* GetChildAt(const int index)const { return m_Children[index]; }

		//todo: think about this, who should have the ability to change the locations
		void SetLocalPosition(const glm::vec3& position);

		glm::vec3 GetWorldPosition();

		//a public functions to indicate to the object that the location has changed
		void SetPositionDirty();
#pragma endregion 
		

	private:
		//todo: order your variables from smallest to largest

		bool m_PositionIsDirty;

		//every object should have a place in the game.
		//it has a local transform and a world transform
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};

		GameObject* m_Parent;

		//todo: ask about shared pointers
		std::vector < std::shared_ptr<BaseComponent>> m_Components{};

		std::vector<GameObject*> m_Children{};


#pragma region private functions
		void AddChild(GameObject* child) { m_Children.push_back(child); }

		void RemoveChild(GameObject* child);

		bool IsChild(GameObject* gameObject);

		void UpdateWorldPosition();
#pragma endregion 
	};

	//template functions

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent()
	{
		for (auto& component : m_Components) {
			if (auto DerivedComponent = std::dynamic_pointer_cast<T>(component)) {
				return DerivedComponent;
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
