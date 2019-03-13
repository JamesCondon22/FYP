#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN	
#include <SFML/Graphics.hpp>
#include "Menus/State.h"


class GameScreen
{
public:
	
	GameScreen(GameState * state);
	void update(double dt);
	void render(sf::RenderWindow & window);

private:

	GameState * m_currentState;
};

#endif
