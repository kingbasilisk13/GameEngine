#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

#include "Texture2D.h"
namespace dae
{
	class Texture2D;
	class BaseComponent;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject(std::shared_ptr<Transform> transform);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		//todo: maybe it is a good idea to add a check that first sees if the game object already has the component and if it does that it deltes the previus component and replaces it with the new one?
		void AddComponent(std::shared_ptr<BaseComponent> component);

		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		template<typename T>
		std::shared_ptr<T> GetComponent();

		template<typename T>
		bool HasComponent();

	private:
		//every object should have a place in the game, so transform is by default added to the game object.
		std::shared_ptr<Transform> m_Transform{};

		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};

		
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
