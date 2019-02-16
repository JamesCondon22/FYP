#include "MathHelper.h"

namespace Math
{
	double distance(sf::Vector2f v1, sf::Vector2f v2)
	{
		
		return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}

	sf::Vector2f lerp(sf::Vector2f &start, sf::Vector2f &end, float value)
	{
		return sf::Vector2f((1.0f - value) * start.x + (value * end.x),
			(1.0f - value) * start.y + (value * end.y));
	}
}