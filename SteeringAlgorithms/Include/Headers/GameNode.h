#pragma once
#include <SFML/Graphics.hpp>

class GameNode
{
public:
	GameNode(int size);
	~GameNode();

	sf::Vector2f getPosition();
	int getRadius();
	void setRadius(int rad);
	void setPosition(sf::Vector2f position);
	void setOrigin(int originX, int originY);
	bool getAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }
	void setColor(sf::Color color);
	void render(sf::RenderWindow & window);

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_position;
	bool m_alive = true;
};

