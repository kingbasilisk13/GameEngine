#pragma once
#include <glm/glm.hpp>

namespace dae
{
	//transform is a struct and not a component because a game object can not exist without a transform.
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		void SetPosition(float x = 0.f, float y = 0.f, float z = 0.f) 
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}
	};
}
