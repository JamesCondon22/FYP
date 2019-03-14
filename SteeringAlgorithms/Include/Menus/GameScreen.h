#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN	
#include <SFML/Graphics.hpp>
#include "Menus/State.h"
#include "Headers/Tile.h"

class GameScreen
{
public:
	
	GameScreen(GameState * state);
	void update(double dt, sf::Vector2i & mouse);
	void render(sf::RenderWindow & window);

private:

	GameState * m_currentState;

	Tile *m_tile[50][50];

	sf::Texture m_texture;
	std::ifstream m_readFile;
	std::ofstream m_file;
	std::string m_line = "";
	bool m_pressed;
};

#endif
