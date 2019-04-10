#pragma once
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"
#include "Headers/Button.h"
#include "Headers/Label.h"
#include <fstream>

class GameMenu
{
public:
	GameMenu(GameState * state, sf::Font & btnfont, sf::Font & font);
	~GameMenu();
	void update(double dt, sf::Window & window);
	void render(sf::RenderWindow& window);
	void initButtons();
	void handleInputs(Button & button);
	void loadData();
	bool m_pressed = true;
	int getActivatedAI() { return m_activatedAI; }
	std::string getLastPressed() { return m_lastPressed; }

private:

	GameState * m_currentState;
	sf::Window m_window;

	std::vector<Button*> m_buttons;
	std::vector<Label*> m_labels;
	sf::Texture m_texture;
	std::ifstream m_file;
	std::string m_line;
	sf::Font m_font;
	sf::Font m_fontTwo;
	sf::Vector2f m_position;
	sf::Vector2i m_mousePosition;
	sf::Event * m_event;
	bool m_renderText = false;
	int m_activatedAI = 0;
	std::string m_lastPressed = "";
};