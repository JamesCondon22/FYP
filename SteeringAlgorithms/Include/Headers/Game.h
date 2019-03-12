#pragma once
#ifndef GAME
#define GAME
#include "Menus/Options.h"
#include "Menus/DemoScreen.h"
#include "Menus/MainMenu.h"

class Game
{
public:
	Game();
	void run();

protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
	
	sf::Texture m_textureEnemy;
	sf::Font m_font;

	MainMenu *mainMenu;
	Options *m_options;
	DemoScreen * m_demoScreen;

	GameState * m_currentState;
};

#endif