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
#include "Path.h"
#include "../Menus/State.h"
#include "Behaviour.h"
#include "Enemy.h"



class Traditional : public Enemy
{
public:
	Traditional(std::vector<GameNode*>  path, std::vector<Obstacle*> obs);
	Traditional() { ; }
	~Traditional();
	float getNewOrientation(float currentOrientation, float velocity);
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f pursue(sf::Vector2f playerPosition);
	void update(double dt, sf::Vector2f player);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	sf::Vector2f getPos();
	void setPosition(sf::Vector2f pos);
	int getId() { return m_id; }
	sf::Vector2f normalize(sf::Vector2f vec);
	sf::Vector2f scale(sf::Vector2f vec, double val);
	void setBehaviourState(BehaviourState* state) { m_currentBehaviour = state; }
	sf::Vector2f ObstacleAvoidance();
	void setState(GameState state) { m_state = state; }
	void setCollided(bool collide) { m_collided = collide; }
	Obstacle * findMostThreathening();
	float distance(sf::Vector2f pos, sf::Vector2f obst);
	bool lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, Obstacle *circle);
	sf::Vector2f truncate(sf::Vector2f v, float const num);
	void setActive(bool active) { m_active = active; }
	bool getActive() { return m_active; }
	int getNodeIndex() { return m_nodeIndex; }
	void generatePath(double dt);
	std::string getName() { return "Traditional"; }
	sf::Color getColor() { return m_color; }
	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	void handleTimer();
	int getRadius() { return m_radius; }
	int getScore() { return m_score;}
	void setScore(int score) { m_score = score; }

	void setVisuals(bool visuals) { m_visuals = visuals; }
	bool getVisuals() { return m_visuals; }
	bool getCollided() { return m_collided; }
	void resetGame();
	double getTime() { return m_currentTime; }
	double getTotalRotation() { return m_totalRotations; }
	void resetDemo();
	void calculateRotations();
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
	float MAX_SPEED = 1.00f;
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

	double m_timeAmount = 0;
	double m_totalPathLength = 0;

	GameState m_state;
	bool m_active = false;
	int m_id = 7;
	int m_nodeIndex = 0;
	sf::CircleShape m_surroundingCircle;

	std::vector<Path*> m_pathLine;

	sf::Color m_color;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	bool m_visuals = true;
	bool m_startTimer = false;

	double m_averageExecTime;
	double m_tickCounter;
	double m_currentTime = 0;
	sf::Clock m_clock;
	BehaviourState* m_currentBehaviour;

	int m_score = 0;
	bool m_collided = false;

	double m_lastRotation;
	double m_totalRotations = 0;
};


