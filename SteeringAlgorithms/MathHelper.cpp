#include "MathHelper.h"

MathHelper::MathHelper()
{
}


MathHelper::~MathHelper()
{
}


sf::Vector2f MathHelper::truncate(sf::Vector2f v, float const num)
{
	float i;
	i = num / thor::length(v);
	i = i < 1.0 ? i : 1.0;
	v *= i;
	return v;
}


sf::Vector2f MathHelper::scale(sf::Vector2f vec, double val)
{
	vec.x = vec.x * val;
	vec.y = vec.y * val;

	return vec;
}
float MathHelper::distance(sf::Vector2f pos, sf::Vector2f obst)
{
	auto dist = sqrt((pos.x - obst.x + 100) * (pos.x - obst.x + 100) + (pos.y - obst.y + 100)*(pos.y - obst.y + 100));
	return dist;
}

bool MathHelper::lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, sf::CircleShape circle)
{
	return distance(circle.getPosition(), vecOne) <= circle.getRadius() || distance(circle.getPosition(), vecTwo) <= circle.getRadius();
}