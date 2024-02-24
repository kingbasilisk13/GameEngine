#pragma once
#include <glm/glm.hpp>

#include "BaseComponent.h"

namespace dae
{
	//a game object will always need a transform component.
	class Transform final : public BaseComponent
	{
	public:
		Transform(float x = 0.f, float y = 0.f, float z = 0.f);

		virtual ~Transform() {};
		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator= (const Transform&) = delete;
		Transform& operator= (const Transform&&) = delete;

		void Update() override;
		void Render() const override;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}
