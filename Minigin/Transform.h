#pragma once
#include <glm/glm.hpp>

namespace dae
{
	//transform is a struct and not a component because a game object can not exist without a transform.
	struct Transform
	{
		glm::vec2 position;

		void SetPosition(const float x = 0.f, const float y = 0.f)
		{
			position.x = x;
			position.y = y;
		}

		void SetPosition(const glm::vec2 newPosition)
		{
			SetPosition(newPosition.x, newPosition.y);
		}
	};
}
