#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Obstacle 
{
public:
	Obstacle(int size, sf::Texture &texture, sf::Vector2f vec, bool isCirc);
	Obstacle(int size);
	~Obstacle();
	void update();
	void render(sf::RenderWindow & window);

	sf::Vector2f getPosition();

	int getRadius();

	void setRadius(int rad);
	void setPosition(sf::Vector2f position);
	void setOrigin(int originX, int originY);
	void setColor(sf::Color color);

private:
	sf::RectangleShape m_rect;
	sf::CircleShape m_circle;

	sf::Texture m_texture;

	sf::Vector2f m_position;
	
	bool m_isCircle;
};

