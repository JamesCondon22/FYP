#pragma once

#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"
#include "Headers/UI/Button.h"
#include "Headers/UI/Label.h"

class MainMenu
{
public:
	MainMenu(GameState * state, sf::Font & font);
	~MainMenu();
	void update(double dt, sf::Window & window);
	void render(sf::RenderWindow& window);
	void initButtons();
	void handleInputs(Button & button);

	bool m_pressed = false;

	int getActivatedAI() { return m_activatedAI; }
	std::string getLastPressed() { return m_lastPressed; }

private:

	GameState * m_currentState;

	sf::Window m_window;
	sf::Event * m_event;
	sf::Texture m_texture;
	sf::Font m_font;
	sf::Vector2i m_mousePosition;

	std::vector<Button*> m_buttons;
	std::string m_lastPressed = "";

	Label* m_header;
	
	int m_activatedAI = 0;
};