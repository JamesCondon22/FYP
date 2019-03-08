#include "../Include/Headers/MathHelper.h"

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


	sf::Vector2f normalize(sf::Vector2f  & vec)
	{
		if (vec.x*vec.x + vec.y * vec.y != 0)
		{
			vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
			vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
		}
		return vec;
	}

	sf::Vector2f scale(sf::Vector2f vec, double val)
	{
		vec.x = vec.x * val;
		vec.y = vec.y * val;

		return vec;
	}

	bool lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, Obstacle* circle)
	{
		return distance(circle->getPosition(), vecOne) <= circle->getRadius() || distance(circle->getPosition(), vecTwo) <= circle->getRadius();
	}
}