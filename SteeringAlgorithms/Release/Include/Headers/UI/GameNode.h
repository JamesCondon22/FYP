#pragma once
#include <SFML/Graphics.hpp>

class GameNode
{
public:
	GameNode(float size, sf::Texture & texture);
	~GameNode();

	int getRadius();

	void setPosition(sf::Vector2f position);
	void setOrigin(int originX, int originY);
	void setAlive(bool alive) { m_alive = alive; }
	void setColor(sf::Color color);
	void render(sf::RenderWindow & window);
	void animateNode();
	void setCompleted(bool complete) { m_completed = complete; }

	bool getAlive() { return m_alive; }
	bool getCompleted() { return m_completed; }

	sf::Vector2f getPosition();
private:
	sf::CircleShape m_circle;
	sf::Vector2f m_position;

	bool animateIn = false;
	bool animateOut = true;
	bool m_alive = true;
	bool m_completed = false;

	float m_radius;
};

