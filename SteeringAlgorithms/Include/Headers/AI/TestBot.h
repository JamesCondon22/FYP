#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include "../UI/Obstacle.h"
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>
#include "../MathHelper.h"
#include "../UI/GameNode.h"


class TestBot
{
public:
	TestBot(std::vector<GameNode*> path, std::vector<Obstacle*> obs);
	~TestBot();

	void update(double dt);
	void render(sf::RenderWindow & window);

	Obstacle * findMostThreathening();

	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f seek();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	sf::Vector2f ObstacleAvoidance();
	sf::Vector2f truncate(sf::Vector2f v, float const num);

	float getNewOrientation(float currentOrientation, float velocity);
	
	int getRadius() { return m_radius; }
	
	void reset();

	void setVisuals(bool visuals) { m_visuals = visuals; }
	bool getVisuals() { return m_visuals; }

private:

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	
	sf::Texture m_texture;
	sf::RectangleShape m_rect;

	const float MAX_SEE_AHEAD = 110.0f;
	const float MAX_AVOID_FORCE = 500.0f;
	const float MAX_FORCE = 10.0f;
	float MAX_SPEED = 0.90f;

	float m_speed;
	float m_rotation;

	sf::Vector2f ahead;
	sf::Vector2f ahead2;
	sf::Vector2f m_heading;
	sf::Vector2f m_steering;
	
	std::vector<sf::RectangleShape> lines;
	std::vector<GameNode*> m_nodes;
	std::vector<Obstacle*> m_obstacles;

	int m_currentNode = 0;
	int m_radius = 30;

	sf::CircleShape m_surroundingCircle;

	bool m_visuals = true;

	const double DEG_TO_RAD = 3.14 / 180;
};


