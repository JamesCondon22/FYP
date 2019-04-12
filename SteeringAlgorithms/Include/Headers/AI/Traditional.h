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
#include "../UI/Path.h"
#include "../../Menus/State.h"
#include "../Behaviour.h"
#include "Enemy.h"


class Traditional : public Enemy
{
public:
	Traditional(std::vector<GameNode*>  path, std::vector<Obstacle*> obs);
	Traditional() { ; }
	~Traditional();
	void update(double dt, sf::Vector2f player);
	void render(sf::RenderWindow & window);
	
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f pursue(sf::Vector2f playerPosition);
	sf::Vector2f getVel();
	sf::Vector2f getPos();
	sf::Vector2f ObstacleAvoidance();
	sf::Vector2f truncate(sf::Vector2f v, float const num);
	
	Obstacle * findMostThreathening();
	
	bool getActive() { return m_active; }
	bool getVisuals() { return m_visuals; }
	bool getCollided() { return m_collided; }

	int getNodeIndex() { return m_nodeIndex; }
	int getId() { return m_id; }
	int getRadius() { return m_radius; }
	int getScore() { return m_score; }

	float getNewOrientation(float currentOrientation, float velocity);
	std::string getName() { return "Traditional"; }
	sf::Color getColor() { return m_color; }

	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	double getTime() { return m_currentTime; }
	double getTotalRotation() { return m_totalRotations; }
	double getAverageRotations();

	void generatePath(double dt);
	void handleTimer();
	void setScore(int score) { m_score = score; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	void resetGame();
	void resetDemo();
	void calculateRotations();
	void setPosition(sf::Vector2f pos);
	void setBehaviourState(BehaviourState* state) { m_currentBehaviour = state; }
	void setState(GameState state) { m_state = state; }
	void setCollided(bool collide) { m_collided = collide; }
	void setActive(bool active) { m_active = active; }
private:
	
	GameState m_state;
	BehaviourState* m_currentBehaviour;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f ahead;
	sf::Vector2f ahead2;

	sf::Vector2f m_heading;
	sf::Vector2f m_steering;

	float m_speed;
	float m_rotation;
	float m_radius = 30;

	sf::Texture m_texture;
	sf::RectangleShape m_rect;

	const double DEG_TO_RAD =  3.14 / 180;
	
	double m_timeAmount = 0;
	double m_totalPathLength = 0;

	int m_score = 0;
	int m_id = 7;
	int m_nodeIndex = 0;
	int m_currentNode = 0;
	
	std::vector<sf::RectangleShape> lines;
	std::vector<GameNode*> m_nodes;
	std::vector<Obstacle*> m_obstacles;
	std::vector<Path*> m_pathLine;
	
	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	bool m_visuals = true;
	bool m_startTimer = false;
	bool m_active = false;
	bool m_collided = false;

	double m_lastRotation;
	double m_totalRotations = 0;
	double m_averageExecTime;
	double m_tickCounter;
	double m_currentTime = 0;

	sf::Clock m_clock;
	sf::Color m_color;
	sf::CircleShape m_surroundingCircle;

	const float MAX_SEE_AHEAD = 110.0f;
	const float MAX_AVOID_FORCE = 500.0f;
	const float MAX_FORCE = 10.0f;
	float MAX_SPEED = 0.98f;
};


