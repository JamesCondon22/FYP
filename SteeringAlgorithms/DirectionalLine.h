#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <map>
#include "ContextMap.h"


class DirectionalLine
{
public:
	DirectionalLine(sf::Vector2f one, double count, double points);
	DirectionalLine() { ; }
	sf::Vector2f getPoints(double x0, double y0, double r, double noOfDividingPoints);
	~DirectionalLine();
	void update(sf::Vector2f position);
	void updatePositions();
	void render(sf::RenderWindow & window);
	sf::Vector2f getPosition();
	void assignDirection();
	std::map<Direction, sf::Vector2f> getMap();
	Direction getState();
	void setRadius(int rad);
	void changeColor();
private:
	sf::Vertex m_line[2];
	std::map<Direction, sf::Vector2f> m_map;
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	int x;
	int y;
	int m_count;
	int m_points;
	Direction m_current;
	int m_radius = 40;
};

