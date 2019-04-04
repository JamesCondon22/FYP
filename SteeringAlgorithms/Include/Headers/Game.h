#pragma once
#ifndef GAME
#define GAME
#include "Menus/Options.h"
#include "Menus/DemoScreen.h"
#include "Menus/Menu.h"
#include "Menus/GameScreen.h"
#include "Menus/EndGame.h"
#include "Menus/GameMenu.h"
#include "Menus/MainMenu.h"
#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"


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
	sf::Texture m_buttonTexture;
	sf::Font m_font;
	sf::Font m_fontBell;
	MainMenu * m_mainMenu;
	Menu *m_menu;
	Options *m_options;
	DemoScreen * m_demoScreen;
	GameScreen * m_gameScreen;
	EndGame * m_endGameScreen;
	GameMenu * m_gameMenu;

	GameState * m_currentState;
	bool m_pressed = false;
	sf::Clock m_clock;

	sf::Vector2i m_mousePosition;
};

#endif