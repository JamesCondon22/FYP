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
	sf::Vector2f getAverage();

	std::map<Direction, sf::Vector2f> getMap();
	
	Direction getState();

	void setRadius(int rad);
	void changeColor();
	void rotateLine(sf::Vector2f position, sf::Vector2f interestPosition, float direction, float angle);
	void calculateAverage(std::vector<int> indices);
	void assignDirection(int count);

	sf::Vector2f getVec(double x0, double y0, double r, double noOfDividingPoints, sf::Vector2f current);
	sf::Vector2f getVector(int ind);

private:

	sf::Vertex m_line[2];

	std::map<Direction, sf::Vector2f> m_map;

	float static const DEG_TO_RAD;
	float static const RAD_TO_DEG;

	int x;
	int y;
	int m_count;
	int m_points;
	int m_radius = 40;

	Direction m_current;
	
	sf::Vector2f averagePosition;
	sf::Vector2f vec;
	sf::Vertex m_mostDesired[2];

	std::string RotateDirection = "";
	std::string LastRotateDirection = "";

	float angle = 0;
};

