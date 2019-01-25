#pragma once
#ifndef FRAYAI
#define FRAYAI
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"

class FrayAI
{
public:
	FrayAI();
	~FrayAI();
	void update(double dt, sf::Vector2f position, std::vector<sf::CircleShape> obstacles);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	void updateLines(sf::Vector2f position);
	void updateDangers(std::vector<sf::CircleShape> obstacles);
	void initVector();
	sf::Vector2f normalize(sf::Vector2f vec);
	void checkDirection();
	void seek(sf::Vector2f position);
	std::vector<std::pair<double, std::string>> normalize(std::vector<std::pair<double, std::string>> vec);
	void normalizeDangers();
	std::vector<std::pair<double, std::string>> normalizeDangers(std::vector<std::pair<double, std::string>> vec);
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	std::pair<double, std::string> findLargest(std::vector<std::pair<double, std::string>> vec);
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
	ContextDecisionMaker mapDecisions;
	sf::CircleShape m_surroundingCircle;

	sf::Vertex line[2]; sf::Vertex line2[2];
	sf::Vertex line3[2]; sf::Vertex line4[2];
	sf::Vertex line5[2]; sf::Vertex line6[2];
	sf::Vertex line7[2]; sf::Vertex line8[2];

	sf::Vector2f UpRadial = sf::Vector2f(0,0);
	std::vector<sf::Vector2f> m_distVecs;
	std::vector<std::pair<double, std::string>> m_distances;
	std::vector<std::pair<double, std::string>> m_distancesDanger;
	double curLargest = 0;
	double curLargestDanger = 0;
	sf::Vector2f curDirection = sf::Vector2f(0, 0);
	
};

#endif