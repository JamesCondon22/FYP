#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Obstacle 
{
public:
	Obstacle(int size);
	Obstacle();
	~Obstacle();

	sf::Vector2f getPositon();
	int getRadius();

	void normalize(sf::Vector2f vec);
	void update();
	void render(sf::RenderWindow & window);

private:
	sf::CircleShape m_rectangle;
	sf::Texture m_texture;
	sf::Vector2f m_position;

};

