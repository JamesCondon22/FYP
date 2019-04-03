#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Obstacle 
{
public:
	Obstacle(int size, sf::Texture &texture, sf::Vector2f vec, bool isCirc);
	Obstacle(int size);
	~Obstacle();

	sf::Vector2f getPosition();
	int getRadius();
	int getID() { return m_id; }
	void setRadius(int rad);
	void setID(int id) { m_id = id; }
	void setPosition(sf::Vector2f position);
	void setOrigin(int originX, int originY);
	void update();
	void render(sf::RenderWindow & window);
	void setColor(sf::Color color);

private:
	sf::CircleShape m_circle;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	int m_id;
	bool m_isCircle;
};

