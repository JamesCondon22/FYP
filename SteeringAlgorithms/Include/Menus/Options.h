#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SFML\Graphics.hpp>
#include "Menus/State.h"

class Options
{
public:
	Options(GameState * state);
	~Options();
	void update(double dt);
	void render(sf::RenderWindow& window);

private:

	GameState * m_currentState;
	sf::Window m_window;
};
#endif // !Options
