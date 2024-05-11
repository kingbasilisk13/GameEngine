#pragma once

namespace dae
{
	struct Rectf
	{
		Rectf()
		{
			left = 0;
			bottom = 0;
			width = 0;
			height = 0;
		}
		explicit Rectf(float left, float bottom, float width, float height);

		float left;
		float bottom;
		float width;
		float height;

	};
}
