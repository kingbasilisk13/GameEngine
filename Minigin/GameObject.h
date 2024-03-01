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
		explicit GameObject(Transform transform);

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		//todo: maybe it is a good idea to add a check that first sees if the game object already has the component and if it does that it deltes the previus component and replaces it with the new one?
		void AddComponent(std::shared_ptr<BaseComponent> component);

		//todo: is there a better way to do this. curently you first need to get a pointer to the component to then delete it.
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		template<typename T>
		std::shared_ptr<T> GetComponent();

		template<typename T>
		bool HasComponent();

		glm::vec3 GetCurrentPosition() const { return m_Transform.position; }

	private:
		//every object should have a place in the game, so transform is by default added to the game object.
		Transform m_Transform{};

		//vector containing all the components. this will need to be changed later when the update order becomes important
		std::vector < std::shared_ptr<BaseComponent>> m_Components{};
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
