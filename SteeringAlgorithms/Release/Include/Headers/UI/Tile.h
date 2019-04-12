#pragma once

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

enum NState
{
	Full,
	Blank,
	Interest,
	Circle,
	KeyObject,
	None,
};


class Tile
{
public:

	Tile(int x, int y, int X, int Y);
	~Tile();
	void render(sf::RenderWindow &window);

	NState getState();

	sf::Vector2f getPosition() { return m_position; }

	bool getObstacle() { return isObstacle; }

	std::pair<int, int> getGridPos() { return m_gridPos; }

	void setColor(sf::Color col);
	void setObstacle();
	void setInterest();
	void setBlank();
	void setCircularObs();
	void setKey();

	int posX;
	int posY;

private:
	sf::RectangleShape m_rect;
	sf::Vector2f m_position;

	bool m_selected = false;
	bool isObstacle;
	bool m_drawInterest = false;

	std::pair<int, int> m_gridPos;

	sf::CircleShape circle;
	sf::CircleShape m_surround;
	sf::CircleShape m_interestPoint;
	sf::CircleShape m_CircleObs;

	NState  m_current;
	

};