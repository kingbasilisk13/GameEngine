#pragma once

#include "Time.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		explicit BaseComponent(GameObject* gameObject) :m_GameObject(gameObject) {};

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void Render(float posX, float posY) const = 0;

		//todo: add some more inheritance to split up components that need to be rendered and those that do not.

		GameObject& GetOwningGameObject() const { return *m_GameObject; }

	private:
		GameObject* m_GameObject;
	};
}



