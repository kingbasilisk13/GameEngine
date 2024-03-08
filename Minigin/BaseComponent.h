#pragma once

#include "GameObject.h"
#include "Time.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		[[nodiscard]] GameObject* GetOwningGameObject() const { return m_GameObject; }

		void SetComponentDirty() { m_ComponentsAreDirty = true; }

	protected:
		explicit BaseComponent(GameObject* gameObject) :m_GameObject(gameObject) {};

		//a flag used to indicate that a component has been deleted. if a component needs another component to work it needs to re check its pointers.
		bool m_ComponentsAreDirty{true};

	private:
		GameObject* m_GameObject;

		virtual void ReloadPointers() { m_ComponentsAreDirty = false; }
	};
}



