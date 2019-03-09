#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include "Obstacle.h"
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>
#include "MathHelper.h"




class TestBot
{
public:
	TestBot(std::vector<sf::CircleShape> & path, std::vector<Obstacle*> obs);
	~TestBot();
	float getNewOrientation(float currentOrientation, float velocity);
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f seek();

	float getRandom(int x, int y);
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	sf::Vector2f ObstacleAvoidance();
	Obstacle * findMostThreathening();
	sf::Vector2f truncate(sf::Vector2f v, float const num);

	int getRadius() { return m_radius; }
private:
	float m_timeToTarget;
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_targetPos;
	float m_speed;
	float m_timePrediction;
	float m_maxTimePrediction;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	float m_distance;
	sf::Texture m_texture;
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Vector2f newPos;
	sf::Vector2f m_relVelocity;
	sf::Vector2f m_relPosition;
	float m_relSpeed;
	sf::Vector2f m_firstRelativePos;
	sf::Vector2f m_firstRelativeVel;

	const float MAX_SEE_AHEAD = 110.0f;
	const float MAX_AVOID_FORCE = 500.0f;
	const float MAX_FORCE = 10.0f;
	float MAX_SPEED = 1.05f;
	float m_threshold;

	sf::Vector2f ahead;
	sf::Vector2f ahead2;

	sf::Vector2f m_heading;
	sf::Vector2f m_steering;
	const double DEG_TO_RAD = 3.14 / 180;

	std::vector<sf::RectangleShape> lines;
	std::vector<sf::CircleShape> m_nodes;
	std::vector<Obstacle*> m_obstacles;
	int currentNode = 0;
	int m_radius = 30;

	sf::CircleShape m_surroundingCircle;
};


