#pragma once
#ifndef PLAYER
#define PLAYER
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	void increaseRotation();
	void decreaseRotation();
	void increaseSpeed();
	void decreaseSpeed();
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	void setPosition(float x, float y);
	int getRadius() { return m_radius; }
	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double m_rotation;
	double m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
	sf::CircleShape m_surround;
	int m_radius = 30;
	int m_score = 0;
};

#endif