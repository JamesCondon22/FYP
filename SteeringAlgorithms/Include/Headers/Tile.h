#pragma once

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

enum NState
{
	Full,
	Blank,
	None,
};


class Tile
{
public:

	Tile(int x, int y, int X, int Y);
	~Tile();
	void render(sf::RenderWindow &window);
	void setPos(int x, int y);
	NState getState();
	sf::Vector2f getPosition();
	bool getObstacle() { return isObstacle; }
	std::pair<int, int> getGridPos() { return m_gridPos; }
	void setColor(sf::Color col);
	void setObstacle();
	void setBlank();
	
	int posX;
	int posY;

private:
	sf::RectangleShape m_rect;
	sf::Vector2f m_position;
	bool m_selected = false;
	bool isObstacle;
	std::pair<int, int> m_gridPos;
	sf::CircleShape circle;

	NState  m_current;

	

};