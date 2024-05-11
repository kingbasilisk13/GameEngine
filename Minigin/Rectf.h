#pragma once

namespace dae
{
	struct Rectf
	{
		Rectf()
		{
			left = 0;
			top = 0;
			width = 0;
			height = 0;
		}
		explicit Rectf(float left, float top, float width, float height);

		float left;
		float top;
		float width;
		float height;

	};
}
