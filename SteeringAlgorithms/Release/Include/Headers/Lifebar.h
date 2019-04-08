#pragma once
#include <SFML\Graphics.hpp>


class LifeBar
{
public:
	LifeBar(sf::Vector2f position);
	~LifeBar();
	void update();
	void render(sf::RenderWindow & window);
	float getLife() { return m_life; }
	
private:

	sf::Vector2f m_position;
	sf::RectangleShape m_bordeRect;
	sf::RectangleShape m_lifeRect;

	float m_life;
	int m_alpha = 255;
};