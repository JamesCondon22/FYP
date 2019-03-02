#pragma once
#include <SFML/Graphics.hpp>
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>

namespace Math
{

	double distance(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f lerp(sf::Vector2f &start, sf::Vector2f &end, float value);
	double newLerp(double &start, double &end, float value);
	
}


