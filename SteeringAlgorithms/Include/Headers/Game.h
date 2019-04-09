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
	void updateGUI();
	void calculateGraphData();
	void initText();
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
	float m_AETarr[7];
	float m_InterTarr[7];
	const float values[7] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f,  0.25f ,  0.25f };
	const char* labels[3] = { "a", "b", "c" };

	const char* tabNames[2] = { "Search","Debugger" };
	int selectedTab = 0;
	bool m_setTimes = false;
	bool onOptions = false;
};

#endif