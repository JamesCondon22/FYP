#pragma once
#include <SFML\Graphics.hpp>

class Path
{
public:
	Path(int size);
	~Path();

	sf::Vector2f getPosition();
	int getRadius();
	void setRadius(int rad);
	void setPosition(sf::Vector2f position);
	void setOrigin(int originX, int originY);
	void render(sf::RenderWindow & window);
	void setColor(sf::Color color);
private:
	sf::CircleShape m_circle;
	sf::Vector2f m_position;
};