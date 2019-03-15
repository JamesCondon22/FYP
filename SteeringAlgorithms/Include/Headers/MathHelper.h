#pragma once
#include <SFML/Graphics.hpp>
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>
#include "Obstacle.h"

namespace Math
{

	double distance(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f lerp(sf::Vector2f &start, sf::Vector2f &end, float value);
	sf::Vector2f normalize(sf::Vector2f & v);
	bool lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, Obstacle* circle);
	sf::Vector2f scale(sf::Vector2f v, double val);
	bool circleCollision(sf::Vector2f v1, sf::Vector2f v2, int r1, int r2);
	float mag(sf::Vector2f & v);
}


