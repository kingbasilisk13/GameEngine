#include "utils.h"

#include "Rectf.h"

float dae::utils::GetDistance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

bool dae::utils::IsOverlapping(const Rectf& r1, const Rectf& r2)
{
	if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
	{
		return false;
	}

	if (r1.top > (r2.top + r2.height) || r2.top > (r1.top + r1.height))
	{
		return false;
	}

	return true;
}
