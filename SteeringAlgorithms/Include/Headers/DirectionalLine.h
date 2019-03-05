#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <map>
#include "ContextMap.h"

struct steering
{
	sf::Vector2f linear;
	float angular;
};

class DirectionalLine
{
public:
	DirectionalLine(sf::Vector2f one, double count, double points);
	DirectionalLine() { ; }
	sf::Vector2f getPoints(double x0, double y0, double r, double noOfDividingPoints);
	~DirectionalLine();
	void update(sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPosition();
	void assignDirection(int count);
	std::map<Direction, sf::Vector2f> getMap();
	Direction getState();
	sf::Vector2f getAverage();
	void setRadius(int rad);
	void changeColor();
	void rotateLine(sf::Vector2f position, sf::Vector2f interestPosition);
	void calculateAverage(std::vector<int> indices);
	
private:
	sf::Vertex m_line[2];
	std::map<Direction, sf::Vector2f> m_map;
	float static const DEG_TO_RAD;
	float static const RAD_TO_DEG;
	int x;
	int y;
	int m_count;
	int m_points;
	Direction m_current;
	int m_radius = 40;
	sf::Vector2f averagePosition;
	sf::Vector2f vec;
	sf::Vertex m_mostDesired[2];

	float angle = 0;
};

