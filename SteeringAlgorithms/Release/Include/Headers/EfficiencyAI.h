#pragma once
#ifndef EFFICIENCYAI
#define EFFICIENCYAI
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"
#include "Obstacle.h"
#include "DirectionalLine.h"

struct steering
{
	sf::Vector2f linear;
	float angular;
};

class EfficiencyAI
{
public:

	EfficiencyAI(std::vector<sf::CircleShape> & path, std::vector<Obstacle*>  obs);
	~EfficiencyAI();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();
	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	sf::Vector2f normalize(sf::Vector2f vec);
	void checkDirection(double dt);
	steering seek(sf::Vector2f position);
	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	double findLargest(std::map<Direction, double> vec);

	void calculation();
	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);
	float mag(sf::Vector2f & v);

private:
	
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	steering m_steering;
	sf::Vector2f m_heading;
	sf::Vector2f UpRadial = sf::Vector2f(0, 0);
	sf::Vector2f curDirection = sf::Vector2f(0, 0);


	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape m_surroundingCircle;


	int size;
	int m_radius = 30;

	
	ContextDecisionMaker mapDecisions;
	

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	
	std::vector<sf::Vector2f> m_distVecs;
	std::vector<sf::CircleShape> m_nodes;
	std::vector<DirectionalLine> m_lineVec;
	std::vector<Obstacle*> m_obstacles;


	int currentNode = 0;
	int currentObs = 0;
	int m_size = 16;
	int m_prevId = 0;


	sf::Time m_timeSinceLastUpdate;
	Direction m_lastDirection;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;

	double m_rotation;
	double m_timeSinceLast = 0;
	float m_speed;
	double MAX_SPEED;
	double MaxDistance = 0;
	double WantedDistance = 0;
	double m_currentDistance = 0;
	double curLargest = 0;
	double curLargestDanger = 0;


	bool startTimer = false;
	bool startMaps = false;
};

#endif