#pragma once
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"
#include "Headers/Button.h"

class GameMenu
{
public:
	GameMenu(GameState * state);
	~GameMenu();
	void update(double dt, sf::Window & window);
	void render(sf::RenderWindow& window);
	void initButtons();
	void checkButtons(std::string name);
	void handleInputs(Button & button);
	bool m_pressed = false;

	int getActivatedAI() { return m_activatedAI; }
	std::string getLastPressed() { return m_lastPressed; }

private:

	GameState * m_currentState;
	sf::Window m_window;

	std::vector<Button*> m_buttons;
	sf::Texture m_texture;

	sf::Font m_font;

	sf::Vector2i m_mousePosition;
	sf::Event * m_event;

	int m_activatedAI = 0;
	std::string m_lastPressed = "";
};