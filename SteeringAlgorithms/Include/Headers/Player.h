#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/UI/Obstacle.h"
#include "Headers/MathHelper.h"

class Player
{
public:
	Player(std::vector<Obstacle*>  obs);
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
	void setPosition(sf::Vector2f pos);
	int getRadius() { return m_radius; }
	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
	void setColor(sf::Color color) { m_color = color; }
	void setAlive(bool alive) { m_alive = alive; }
	bool getAlive() { return m_alive; }
	void reset();
	sf::Color getColor() { return m_color; }
	void obstacleCollision();
	std::string getName() { return "Player"; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	bool getVisuals() { return m_visuals; }
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
	sf::Color m_color;
	std::vector<Obstacle*> m_obstacles;
	bool m_visuals = true;
	bool m_alive = true;
};