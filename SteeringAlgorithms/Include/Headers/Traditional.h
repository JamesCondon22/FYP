#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include "Obstacle.h"
#include <Thor\Math.hpp>
#include <Thor/Vectors.hpp>
#include "MathHelper.h"
#include "GameNode.h"



class Traditional
{
public:
	Traditional(std::vector<GameNode*>  path, std::vector<Obstacle*> obs);
	~Traditional();
	float getNewOrientation(float currentOrientation, float velocity);
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f pursue(sf::Vector2f playerPosition);
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void update(double dt, sf::Vector2f player);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	int getId() { return m_id; }
	sf::Vector2f normalize(sf::Vector2f vec);
	sf::Vector2f scale(sf::Vector2f vec, double val);

	sf::Vector2f ObstacleAvoidance();
	Obstacle * findMostThreathening();
	float distance(sf::Vector2f pos, sf::Vector2f obst);
	bool lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, Obstacle *circle);
	sf::Vector2f truncate(sf::Vector2f v, float const num);
	void setActive(bool active) { m_active = active; }
	bool getActive() { return m_active; }
private:
	float m_timeToTarget;
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_targetPos;
	float m_speed;
	
	float m_rotation;
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
	float m_radius = 30;
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
	const double DEG_TO_RAD =  3.14 / 180;
	
	std::vector<sf::RectangleShape> lines;
	std::vector<GameNode*> m_nodes;
	std::vector<Obstacle*> m_obstacles;
	int currentNode = 0;

	bool m_active = false;
	int m_id = 7;

	sf::CircleShape m_surroundingCircle;
};


