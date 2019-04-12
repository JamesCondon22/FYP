#pragma once
#include <SFML/Graphics.hpp>
#include "../MathHelper.h"
class Key
{
public:
	Key(sf::Texture & texture);
	Key() { ; }
	~Key() { ; }

	void update(double dt);
	void render(sf::RenderWindow & window);
	void checkCollision(sf::Vector2f position, float rad);
	void setPosition(sf::Vector2f position) { m_position = position; }
	void setActivated(bool active) { m_activated = active; }
	void setCollision(bool collide) { m_collision = collide; }

	bool getActive() { return m_activated; }
	bool getCollision() { return m_collision; }

	sf::Vector2f getPosition() { return m_position; }
private:
	sf::Vector2f m_position;
	
	sf::Texture m_texture;

	sf::RectangleShape m_rect;
	sf::CircleShape m_surround;

	bool m_activated = false;
	bool m_collision = false;

};