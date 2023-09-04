#pragma once

#include <cmath>

class Math
{
public:
	static unsigned int Align(unsigned int position, unsigned int alignment)
	{
		return alignment == 0 ? alignment : ceil((double)position / alignment) * alignment;
	}

	static float Clamp(float value, float minimum, float maximum)
	{
		if (value < minimum)
		{
			return minimum;
		}
		else if (value > maximum)
		{
			return maximum;
		}

		return value;
	}
};
