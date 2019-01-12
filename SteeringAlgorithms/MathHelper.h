#pragma once
#include <SFML/Graphics.hpp>
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>

class MathHelper
{
public:
	MathHelper();
	~MathHelper();

	sf::Vector2f truncate(sf::Vector2f v, float const num);
	float distance(sf::Vector2f pos, sf::Vector2f obst);
	bool lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, sf::CircleShape circle);
	sf::Vector2f scale(sf::Vector2f vec, double val);
};

