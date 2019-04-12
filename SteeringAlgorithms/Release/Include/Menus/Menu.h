#pragma once
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"
#include "Headers/UI/Button.h"

class Menu
{
public:
	Menu(GameState * state, sf::Font & font);
	~Menu();
	void update(double dt, sf::Window & window);
	void render(sf::RenderWindow& window);
	void initButtons();
	void checkButtons(std::string name);
	void handleInputs(Button & button);
	bool m_pressed = true;
	void resetButtons();
	int getActivatedAI() { return m_activatedAI; }
	std::string getLastPressed() { return m_lastPressed; }
	void setLast();
private:

	GameState * m_currentState;
	sf::Window m_window;

	std::vector<Button*> m_buttons;
	sf::Texture m_texture;

	sf::Font m_font;

	sf::Vector2i m_mousePosition;
	sf::Event * m_event;

	Button * m_lastButton;

	std::string m_lastPressed = "";

	int m_activatedAI = 0;
	bool m_reset = false;
	
};