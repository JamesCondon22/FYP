#pragma once
#ifndef INTERPOLATINGTWO_H
#define INTERPOLATINGTWO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"
#include "Obstacle.h"
#include "DirectionalLine.h"

class InterpolatingTwo
{
public:
	InterpolatingTwo(std::vector<sf::CircleShape> & path, std::vector<Obstacle*>  obs);
	~InterpolatingTwo();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();
	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	sf::Vector2f normalize(sf::Vector2f vec);
	void checkDirection();
	steering seek(sf::Vector2f position);
	void calculation();
	float mag(sf::Vector2f & v);

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	double findLargest(std::map<Direction, double> vec);

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	bool compareKeys(std::map<Direction, sf::Vector2f> vec);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	steering m_steering;

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	double m_rotation;
	float m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
	ContextDecisionMaker mapDecisions;
	sf::CircleShape m_surroundingCircle;

	std::vector<std::pair<sf::Vertex, sf::Vertex>> LINES;
	sf::Vertex line[2]; sf::Vertex line2[2];
	sf::Vertex line3[2]; sf::Vertex line4[2];
	sf::Vertex line5[2]; sf::Vertex line6[2];
	sf::Vertex line7[2]; sf::Vertex line8[2];
	sf::Vertex line9[2]; sf::Vertex line10[2];
	sf::Vertex line11[2]; sf::Vertex line12[2];
	sf::Vertex line13[2]; sf::Vertex line14[2];
	sf::Vertex line15[2]; sf::Vertex line16[2];

	sf::Vector2f UpRadial = sf::Vector2f(0,0);
	std::vector<sf::Vector2f> m_distVecs;
	/*std::vector<std::pair<double, std::string>> m_distances;
	std::vector<std::pair<double, std::string>> m_distancesDanger;*/

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	std::vector<double> m_distancesDangerCopy;

	double curLargest = 0;
	double curLargestDanger = 0;
	sf::Vector2f curDirection = sf::Vector2f(0, 0);
	int m_radius = 30;

	std::vector<sf::CircleShape> m_nodes;
	int currentNode = 0;

	std::vector<Obstacle*> m_obstacles;
	int currentObs = 0;

	int m_size = 16;
	std::vector<DirectionalLine> m_lineVec;
};

#endif